#include "ThreadPacket.h"

ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
}

const quint8    ThreadPacket::packetDirectionsNumber = 8;
packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUnknow,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketFile,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketConfig,
    &ThreadPacket::PacketModule
};

ThreadPacket::~ThreadPacket()
{
    client->threadFinished();
}

void ThreadPacket::run()
{
    CommPacket pac;
    client->stream >> pac;
    if (pac.packetType < packetDirectionsNumber)
        (this->*packetDirections[ pac.packetType ])();
    else
        PacketUnknow();
}

void ThreadPacket::PacketUnknow()
{//maybe disconect
    qDebug() << "[ in] Unknow packet....";
    client->packetRead();
}

void ThreadPacket::PacketError()
{
}

void ThreadPacket::PacketInit()
{
    CommInit init;
    client->stream >> init;
    client->packetRead();
}

void ThreadPacket::PacketAlive()
{
    client->packetRead();
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;
    client->packetRead();
}

void ThreadPacket::PacketFile()
{
    client->packetRead();
}

void ThreadPacket::PacketConfig()
{
    client->packetRead();
}

void ThreadPacket::PacketModule()
{
    static int i = 0;
    int j = i++;
    CommModule mod;
    client->stream >> mod;
    client->packetRead();
    qDebug() << "a long work start (2s) no:" << j;
    sleep(2);
    qDebug() << "a long work end no:" << j;
}
