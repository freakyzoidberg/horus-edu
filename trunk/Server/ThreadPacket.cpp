#include "ThreadPacket.h"

const quint8    ThreadPacket::packetDirectionsNumber = 6;
packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUnknow,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketFile,
    &ThreadPacket::PacketUnknow,//&ThreadPacket::PacketConfig,
    &ThreadPacket::PacketModule
};

ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
}

void ThreadPacket::run()
{
    CommPacket pac;
    client->stream >> pac;
    if (pac.type < packetDirectionsNumber)
        (this->*packetDirections[ pac.type ])();
}

void ThreadPacket::PacketUnknow()
{
    qDebug() << "[ in Packet ] type = Login";
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
