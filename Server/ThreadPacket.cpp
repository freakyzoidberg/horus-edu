#include "ThreadPacket.h"
#include "Sql.h"
#include <QMutex>
#include "Server.h"


ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
    client->threadStart();
}

ThreadPacket::~ThreadPacket()
{
    client->threadFinished();
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
    {
        qDebug() << n << "unknow packets received.";
        client->packetReceived();
        qDebug() << n << "unknow packets recived.";
        Sql *Mycon = new Sql();
        QSqlQuery* query = Mycon->query();

        while (query->next()) {
            QString login = query->value(1).toString();
            qDebug() << login;
        }
        delete query;
        delete Mycon;
    }

    // and redirect to the good method
    if (pac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ pac.packetType ])();
    else
        client->packetReceived();
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
    client->packetReceived();
}

void ThreadPacket::PacketInit()
{
    CommInit init;
    client->stream >> init;
    client->packetReceived();
}

void ThreadPacket::PacketAlive()
{
    client->packetReceived();
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;
    client->packetReceived();
}

void ThreadPacket::PacketFile()
{
    client->packetReceived();
}

void ThreadPacket::PacketConfig()
{
    client->packetReceived();
}

void ThreadPacket::PacketModule()
{
    static int i = 0;
    int j = i++;
    CommModule mod;
    client->stream >> mod;
    client->packetReceived();

    qDebug() << "a long work start (2s) no:" << j;
    sleep(2);
    qDebug() << "a long work end no:" << j;
}
