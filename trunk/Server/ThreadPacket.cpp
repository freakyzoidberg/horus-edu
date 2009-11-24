#include <QDateTime>

#include "ThreadPacket.h"
#include "../Common/DataManager.h"
#include "PluginManagerServer.h"
#include "../Common/UserDataPlugin.h"
#include "../Common/CommInit.h"
#include "../Common/CommData.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "NetworkPlugin.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    PluginManagerServer::instance()->setCurrentUser(socket->user);
    CommPacket pac(packet);
    // redirect to the good method
    (this->*packetDirections[ pac.packetType ])();
	PluginManagerServer::instance()->threadFinnished();
}

ThreadPacket::packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUndefined,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketData,
    &ThreadPacket::PacketPlugin
};

void ThreadPacket::PacketUndefined()
{
//    CommPacket p(CommPacket::UNDEFINED);
}

void ThreadPacket::PacketError()
{
//    CommError err(packet);
}

void ThreadPacket::PacketInit()
{
    CommInit init(packet);

    if (socket->status != ClientSocket::INIT)
        return sendError(CommError::ALREADY_INITIALIZED);

    socket->status = ClientSocket::CONNECTED;
}

void ThreadPacket::PacketAlive()
{
    CommPacket a(CommPacket::ALIVE);
    emit sendPacket(a.getPacket());
}

void ThreadPacket::PacketLogin()
{
    CommLogin login(packet);

    // wait other threads for this connexion if needed
    socket->waitOtherThreads();

    if (socket->status != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if (login.method != CommLogin::LOGIN_PASSWORD && login.method != CommLogin::LOGIN_SESSION && login.method != CommLogin::LOGOUT)
        return sendError(CommError::PROTOCOL_ERROR);

    UserDataPlugin* plugin = PluginManagerServer::instance()->findPlugin<UserDataPlugin*>();
    if ( ! plugin)
        return sendError(CommError::INTERNAL_ERROR, "No UserDataPlugin found. Cannot authenticate the user.");

    UserData* user = 0;
    if (login.method == CommLogin::LOGIN_SESSION)
		user = plugin->authenticateSession(login.login, login.sessionString);

    else if (login.method == CommLogin::LOGIN_PASSWORD)
		user = plugin->authenticatePassword(login.login, login.password);

    else if (socket->user)
    {
        ClientSocket::connectedUsers.remove(socket->user);
		socket->user->destroySession();
        socket->user = 0;
        CommLogin resp(CommLogin::DISCONNECTED);
        emit sendPacket(resp.getPacket());
        return;
    }

    if ( ! user)
    {
        CommLogin resp(CommLogin::REFUSED);
        emit sendPacket(resp.getPacket());
        return;
    }

    // if the user is already connected, disconnect him from the other socket
    if (socket->connectedUsers.contains(user))
    {
        connect(this, SIGNAL(sendPacketToAnotherSocket(QByteArray)), ClientSocket::connectedUsers[user], SLOT(sendPacket(QByteArray)));
        emit sendPacketToAnotherSocket( CommLogin(CommLogin::DISCONNECTED).getPacket() );
        ClientSocket::connectedUsers[user]->user = 0;
    }
    ClientSocket::connectedUsers[user] = socket;
    socket->user = user;
    PluginManagerServer::instance()->setCurrentUser(socket->user);

	// get every data the user need to be up to date
	QList<Data*> list;
	foreach (DataPlugin* p, PluginManagerServer::instance()->findPlugins<DataPlugin*>())
		foreach (Data* d, p->allDatas())
			if (d->status() != Data::EMPTY && d->canAccess(user)) //TODO && lastChange > last time user is upto date
				list.append(d);

    CommLogin resp(CommLogin::ACCEPTED);
    resp.serverDateTime = QDateTime::currentDateTime();
    resp.sessionEnd = QDateTime::currentDateTime().addSecs( DEFAULT_SESSION_LIFETIME * 60 );
	resp.sessionString = socket->user->newSession(resp.sessionEnd);
    resp.user = user;
	resp.nbrDataForUpdate = list.count();
    emit sendPacket(resp.getPacket());

	//now send the datas to user, to be uptodate
	foreach (Data* data, list)
		data->sendToUser(user);

    //allow other threads to be started
    socket->allowOtherThreads();
}

void ThreadPacket::PacketData()
{
    CommData data(packet);
    foreach (DataPlugin* plugin, PluginManagerServer::instance()->findPlugins<DataPlugin*>())
		if (plugin->dataType() == data.type)
            plugin->dataManager->receiveData(socket->user, data.data);
}

void ThreadPacket::PacketPlugin()
{
    CommPlugin mod(packet);

    if (socket->status != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user)
        return sendError(CommError::NOT_AUTHENTICATED);

    QString target = mod.packet.targetPlugin;

    NetworkPlugin* plugin = PluginManagerServer::instance()->findPlugin<NetworkPlugin*>(target);
    mod.packet.user = socket->user;
    if (plugin)
        return plugin->receivePacket(socket->user, mod.packet);

    mod.packet.targetPlugin = mod.packet.sourcePlugin;
    mod.packet.sourcePlugin = target;
    mod.packet.error = 1;
    mod.packet.errorMessage = "Plugin " + target + " not found or doesn't receive PluginPacket.";
    emit sendPacket(CommPlugin(mod.packet).getPacket());
}

void ThreadPacket::sendError(CommError::Error error, const char* str) const
{
    emit sendPacket(CommError(error, str).getPacket());
}
