#include "ThreadPacket.h"

const quint8    ThreadPacket::packetDirectionsNumber = 6;
packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUnknow,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketConfig,
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
}

void ThreadPacket::PacketAlive()
{
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;
}

void ThreadPacket::PacketFile()
{
}

void ThreadPacket::PacketConfig()
{
}

void ThreadPacket::PacketModule()
{
}
