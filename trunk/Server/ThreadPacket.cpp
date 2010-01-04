/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <QDateTime>

#include "ThreadPacket.h"
#include "../Common/DataManager.h"
#include "PluginManagerServer.h"
#include "../Common/UserDataPlugin.h"
#include "../Common/CommInit.h"
#include "../Common/CommData.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "AuthenticationPlugin.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
	PluginManagerServer::instance()->setCurrentUser(socket->user);
	CommPacket pac(packet);

	if (pac.packetType > 3) //if packet login, data or plugin
		if (socket->status != ClientSocket::CONNECTED) // check if initialized
			return sendError(CommError::NOT_INITIALIZED);

	if (pac.packetType > 4) //if packet data or plugin
		if ( ! socket->user) // check if connected
			return sendError(CommError::NOT_AUTHENTICATED);


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

    if (login.method != CommLogin::LOGIN_PASSWORD && login.method != CommLogin::LOGIN_SESSION && login.method != CommLogin::LOGOUT)
        return sendError(CommError::PROTOCOL_ERROR);

	AuthenticationPlugin* plugin = PluginManagerServer::instance()->findPlugin<AuthenticationPlugin*>();
    if ( ! plugin)
		return sendError(CommError::INTERNAL_ERROR, "No AuthenticationPlugin found. Cannot authenticate the user.");

    UserData* user = 0;
    if (login.method == CommLogin::LOGIN_SESSION)
		user = plugin->authenticateSession(login.login, login.sessionString);

    else if (login.method == CommLogin::LOGIN_PASSWORD)
		user = plugin->authenticatePassword(login.login, login.password);

    else if (socket->user)
    {
        ClientSocket::connectedUsers.remove(socket->user);
		plugin->destroySession(socket->user);
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


	QList<Data*> list = datasNeedUpdate(login.dataForUpdate);


    CommLogin resp(CommLogin::ACCEPTED);
    resp.serverDateTime = QDateTime::currentDateTime();
    resp.sessionEnd = QDateTime::currentDateTime().addSecs( DEFAULT_SESSION_LIFETIME * 60 );
	resp.sessionString = plugin->createSession(user, resp.sessionEnd);
    resp.user = user;
	resp.nbrDataUpdated = list.count();
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

QList<Data*> ThreadPacket::datasNeedUpdate(const QByteArray& buff) const
{
	// get every data the user can access
	QList<Data*> list;
	foreach (DataPlugin* p, PluginManagerServer::instance()->findPlugins<DataPlugin*>())
	{
		p->userConnected(socket->user);
		foreach (Data* d, p->allDatas())
			if (d->status() != Data::EMPTY && d->canAccess(socket->user))
				list.append(d);
	}

	QDataStream streamAll(buff);
	PluginManagerServer* pluginManager = PluginManagerServer::instance();
	QHash<QString,DataPlugin*> plugins;
	foreach (DataPlugin* plugin, pluginManager->findPlugins<DataPlugin*>())
		plugins.insert(plugin->dataType(), plugin);

	while (! streamAll.atEnd())
	{
		QString type;
		QByteArray binPlugin;
		streamAll >> type >> binPlugin;

		if (plugins.contains(type))
		{
			QDataStream streamPlugin(&binPlugin, QIODevice::ReadOnly);
			while ( ! streamPlugin.atEnd())
			{
				Data* data = plugins.value(type)->dataWithKey(streamPlugin);
				QDateTime lastChange;
				streamPlugin >> lastChange;
				if (data->lastChange() == lastChange)
					list.removeOne(data);
				else if ( ! list.contains(data))
					list.append(data);
			}
		}
	}
	return list;
}
