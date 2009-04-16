#include "ThreadPacket.h"
#include "Server.h"
#include "PluginManager.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    CommPacket pac(packet);

    if (pac.packetType == CommPacket::UNKNOW)
        return;

    // redirect to the good method
   (this->*packetDirections[ pac.packetType ])();
}

packetDirection ThreadPacket::packetDirections[] =
{
    0,//for CommPacket::UNKNOW
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketConfig,
    &ThreadPacket::PacketModule
};

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

    User* user = new User(socket);

    if (login.loginType == CommLogin::LOGIN_SESSION)
        user->login(login.login, true, login.sessionString);
    else if (login.loginType == CommLogin::LOGIN_PASSWORD)
        user->login(login.login, false, login.sha1Pass);

    if ( ! socket->userId)
    {
        CommLogin response(CommLogin::REFUSED);
        emit sendPacket(response.getPacket());
        qDebug() << "[out]" << response;
        delete user;
        return;
    }

    CommLogin response(CommLogin::ACCEPTED);
    response.sessionString = user->getSession();
    response.sessionTime = DEFAULT_SESSION_LIFETIME;
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
}

void ThreadPacket::PacketModule()
{
    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);

    if ( ! socket->userId)
      return sendError(CommError::NOT_AUTHENTICATED);

    CommModule mod(packet);
    qDebug() << "[ in]" << mod;

    IServerPlugin* plugin = PluginManager::globalInstance()->getPlugin(mod.targetModule);
    if (plugin)
        plugin->recvPacket(socket->userId, mod);

    //const ModulePacket& m = mod;

    //client->stream >> mod;
//    finishReading();

/*
    Sql con;
    QSqlQuery query("SELECT * FROM testdb", QSqlDatabase::database(con));
    while (query.next())
        qDebug() << query.value(1).toString();
        */
    /* ou pour pouvoir debloquer quand on veu:
    Sql* con = new Sql;
    QSqlQuery* query("SELECT * FROM testdb", QSqlDatabase::database(*con));
    ...
    delete query;
    delete con;// <- Debloque
    */
    usleep(100000);
}

void ThreadPacket::sendError(CommError::eType error, const char* str)
{
    CommError err(error, str);
    emit sendPacket(err.getPacket());
}
