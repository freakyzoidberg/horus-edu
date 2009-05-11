#include <QDateTime>

#include "ThreadPacket.h"

#include "Server.h"
#include "PluginManager.h"
#include "User.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommFile.h"
#include "../Common/CommSettings.h"


//ZoidTest
#include "TreeMngt.h"

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

packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUndefined,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketConfig,
    &ThreadPacket::PacketModule
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
    emit sendPacket(a.getPacket());
    qDebug() << "[ in]" << a;
    qDebug() << "[out]" << a;
}

void ThreadPacket::PacketLogin()
{
    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    CommLogin login(packet);
    qDebug() << "[ in]" << login;

    if (login.method != CommLogin::LOGIN_PASSWORD && login.method != CommLogin::LOGIN_SESSION)
      return sendError(CommError::NOT_INITIALIZED);

    User* user = new User(socket);

    if (login.method == CommLogin::LOGIN_SESSION)
        user->login(login.login, true, login.sessionString);
    else
        user->login(login.login, false, login.sha1Pass);

    if ( ! socket->userId)
    {
        CommLogin response(CommLogin::REFUSED);
        emit sendPacket(response.getPacket());
        qDebug() << "[out]" << response;
        delete user;
        return;
    }

    user->renewSession(DEFAULT_SESSION_LIFETIME * 60);
    CommLogin response(CommLogin::ACCEPTED);
    response.sessionString = user->getSessionString();
    response.sessionTime = user->getSessionEnd().toTime_t() - QDateTime::currentDateTime().toTime_t();

    emit sendPacket(response.getPacket());
    socket->allowOtherThreads();
    qDebug() << "[out]" << response;
}

void ThreadPacket::PacketFile()
{
    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);
}

void ThreadPacket::PacketConfig()
{
    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    if ( ! socket->userId)
      return sendError(CommError::NOT_AUTHENTICATED);

}

void ThreadPacket::PacketModule()
{
    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);

    if ( ! socket->userId)
      return sendError(CommError::NOT_AUTHENTICATED);

    int len = packet.length();
    CommModule mod(packet);
    qDebug() << "[ in]" << mod << "length:" << len;

    IServerPlugin* plugin = PluginManager::globalInstance()->getPlugin(mod.packet.targetModule);
    if (plugin)
        plugin->recvPacket(socket->userId, mod.packet);

    //ZoidTest
    //TreeMngt test;
     //test.UpdateVector();


    //test.DeleteNode(4);
    //test.MoveNode(14, 1);
    //test.SetName(14, "test SETNAME");
    //test.SetUserRef(14, 4);
    //test.InsertNode("inserted1", 0, 4);

}

void ThreadPacket::sendError(CommError::eType error, const char* str)
{
    CommError err(error, str);
    qDebug() << "[out]" << err;
    emit sendPacket(err.getPacket());
}
