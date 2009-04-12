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
    if (n)
        qDebug() << n << "unknow packets received from client" << client->id;

    // and redirect to the good method
    if (pac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ pac.packetType ])();

    finishReading();

    //emit threadFinished();
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
    //static int i = 0;
    //int j = i++;
    CommModule mod;
    client->stream >> mod;
    finishReading();


    Sql *Mycon = new Sql();
        QSqlQuery* query = Mycon->query("SELECT * FROM testdb");
        while (query->next()) {
            QString login = query->value(1).toString();
            qDebug() << login;
        }
        delete query;
        delete Mycon;

//    sleep(1);
}

void ThreadPacket::writeError(CommError::eType err, const char* str)
{
    client->writeStream.lock();
    //CommError err(err, str);
    client->writeStream.unlock();
}

void ThreadPacket::finishReading()
{
    if ( ! finishReadingFlag)
        emit readFinished();
    finishReadingFlag = true;
}
