#include <QDateTime>

#include "ThreadPacket.h"

#include "PluginManager.h"
#include "User.h"
#include "UserSettings.h"
#include "FileTransfert.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommFile.h"
#include "../Common/CommSettings.h"

//ZoidTest
#include "Tree.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    CommPacket pac(packet);
    // redirect to the good method
   (this->*packetDirections[ pac.packetType ])();
}

ThreadPacket::packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUndefined,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketSettings,
    &ThreadPacket::PacketPlugin
};

void ThreadPacket::PacketUndefined()
{
    CommPacket p(CommPacket::UNDEFINED);
    qDebug() << "[ in]" << p;
}

void ThreadPacket::PacketError()
{
    CommError err(packet);
    qDebug() << "[ in]" << err;
}

void ThreadPacket::PacketInit()
{
    CommInit init(packet);
    qDebug() << "[ in]" << init;

    if (socket->vState != ClientSocket::INIT)
        return sendError(CommError::ALREADY_INITIALIZED);

    socket->vState = ClientSocket::CONNECTED;
}

void ThreadPacket::PacketAlive()
{
    CommPacket a(CommPacket::ALIVE);
    qDebug() << "[ in]" << a;

    emit sendPacket(a.getPacket());
    qDebug() << "[out]" << a;
}

void ThreadPacket::PacketLogin()
{
    CommLogin login(packet);
    qDebug() << "[ in]" << login;

    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    if (login.method != CommLogin::LOGIN_PASSWORD &&
        login.method != CommLogin::LOGIN_SESSION &&
        login.method != CommLogin::LOGOUT)
      return sendError(CommError::PROTOCOL_ERROR);

    socket->waitOtherThreads();

    User& user = socket->user;
    user.init();

    if (login.method == CommLogin::LOGOUT)
        user.logout();
    else if (login.method == CommLogin::LOGIN_SESSION)
        user.login(login.login, true, login.sessionString);
    else
        user.login(login.login, false, login.sha1Pass);

    if ( ! user.isLoggedIn())
    {
        CommLogin response(CommLogin::REFUSED);
        emit sendPacket(response.getPacket());
        qDebug() << "[out]" << response;
        return;
    }

    user.renewSession(DEFAULT_SESSION_LIFETIME * 60);
    CommLogin response(CommLogin::ACCEPTED);
    response.sessionString = user.getSessionString();
    response.sessionTime =   user.getSessionEnd().toTime_t() - QDateTime::currentDateTime().toTime_t();

    emit sendPacket(response.getPacket());
    socket->allowOtherThreads();
    qDebug() << "[out]" << response;
}

void ThreadPacket::PacketFile()
{
    CommFile f(packet);
    qDebug() << "[ in]" << f;

    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    if ( ! socket->user.isLoggedIn())
      return sendError(CommError::NOT_AUTHENTICATED);

    QFile* file = new QFile("/tmp/test");
    file->open(QFile::ReadOnly);

    FileTransfert* ft = new FileTransfert(file);
    CommFile resp(CommFile::FILE, 0);
    resp.key = ft->getKey();
    emit sendPacket(resp.getPacket());
    qDebug() << "[out]" << resp;
}

void ThreadPacket::PacketSettings()
{
    int len = packet.length();
    CommSettings s(packet);
    qDebug() << "[ in]" << s << "length" << len ;

    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user.isLoggedIn())
        return sendError(CommError::NOT_AUTHENTICATED);
    if (s.method != CommSettings::GET && s.method != CommSettings::SET)
        return sendError(CommError::PROTOCOL_ERROR);

    if ( s.scope == CommSettings::CLIENT_USER_SCOPE   || s.scope == CommSettings::SERVER_USER_SCOPE || //USER_SCOPE
        (s.scope == CommSettings::CLIENT_SYSTEM_SCOPE && s.method == CommSettings::GET) || //Read Client SYSTEM_SCOPE
        socket->user.getLevel() <= User::ADMINISTRATOR) // ADMIN
    {
        UserSettings userSettings(socket->user.getId(), s.plugin, s.scope);

        if (s.method == CommSettings::SET)
            userSettings.set(s.getBinarySettings());

        s.method = CommSettings::VALUE;
        s.setBinarySettings(userSettings.get());
    }
    else
        s.method = CommSettings::PERMISSION_DENIED;

    sendPacket(s.getPacket());
    qDebug() << "[out]" << s;
}

void ThreadPacket::PacketPlugin()
{
    int len = packet.length();
    CommPlugin mod(packet);
    qDebug() << "[ in]" << mod << "length:" << len;

    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user.isLoggedIn())
        return sendError(CommError::NOT_AUTHENTICATED);

    IServerPlugin* plugin = PluginManager::globalInstance()->getPlugin(mod.packet.targetPlugin);
    if (plugin)
    {
        plugin->recvPacket(socket->user.getId(), mod.packet);
        ((InterfaceServer*)plugin->server)->cleanInterface();
    }
    // else TODO send an error "Plugin not found"

}

void ThreadPacket::sendError(CommError::Error error, const char* str) const
{
    CommError err(error, str);
    qDebug() << "[out]" << err;
    emit sendPacket(err.getPacket());
}
