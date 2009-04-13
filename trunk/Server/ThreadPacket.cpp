#include "ThreadPacket.h"
#include "Server.h"

ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
    finishReadingFlag = false;
}

void ThreadPacket::run()
{
    CommPacket pac;

    quint32 n;
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
        qDebug() << n << "unknow packets received from client" << client->id;

    // and redirect to the good method
    if (pac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ pac.packetType ])();

    finishReading();
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
    CommError err;
    client->stream >> err;
}

void ThreadPacket::PacketInit()
{
    CommInit init;
    client->stream >> init;
}

void ThreadPacket::PacketAlive()
{
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;

    User usr;
    usr.loginPassword(login.login, login.sha1Pass);

//    if (client->state == ClientSocket::INIT)
//      writeError(CommError::NOT_INITIALIZED);

}

void ThreadPacket::PacketFile()
{
}

void ThreadPacket::PacketConfig()
{
}

void ThreadPacket::PacketModule()
{
    CommModule mod;
    client->stream >> mod;
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
//    usleep(100);
}

void ThreadPacket::writeError(CommError::eType error, const char* str)
{
    CommError err(error, str);
    client->writeStream.lock();
    client->stream << err;
    client->writeStream.unlock();
}

void ThreadPacket::finishReading()
{
    if ( ! finishReadingFlag)
        emit readFinished();
    finishReadingFlag = true;
}
