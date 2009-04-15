#include "ThreadPacket.h"
#include "Server.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    CommPacket pac(packet);

    /*quint32 n;
    // Look for a valid header
    for (n=0; client->socket.bytesAvailable(); n++)
    {
        client->stream >> pac;
        if (pac.packetType != CommPacket::UNKNOW)
            break;
    }
    //if invalid packets are found
    //MAYBE DISCONNECT if there is nn more errors
    if (n)
        qDebug() << n << "unknow packets received from client" << client->id;*/

    // redirect to the good method
    if (pac.packetType != CommPacket::UNKNOW)
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
    if (socket->user.getState() != User::INIT)
        sendError(CommError::ALREADY_INITIALIZED);
    else
        socket->user.init();
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
    if (socket->user.getState() == User::INIT)
      sendError(CommError::NOT_INITIALIZED);

    CommLogin login(packet);
    qDebug() << "[ in]" << login;

    CommLogin response(CommLogin::REFUSED);

    if (
        (login.loginType == CommLogin::LOGIN_PASSWORD && socket->user.loginPassword(login.login, login.sha1Pass))
        ||
        (login.loginType == CommLogin::LOGIN_SESSION  && socket->user.loginSession (login.login, login.sessionString))
       )
    {
        response.loginType = CommLogin::ACCEPTED;
        response.sessionString = socket->user.newSession();
        response.sessionTime = DEFAULT_SESSION_LIFETIME;
        socket->allowOtherThreads();
    }

    emit sendPacket(response.getPacket());
    qDebug() << "[out]" << response;

    //        sendError(CommError::);


}

void ThreadPacket::PacketFile()
{
}

void ThreadPacket::PacketConfig()
{
}

void ThreadPacket::PacketModule()
{
    CommModule mod(packet);
    qDebug() << "[ in]" << mod;

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
