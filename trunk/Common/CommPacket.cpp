#include "CommPacket.h"

CommPacket::CommPacket(pType _type)
{
    packetType = _type;
}

CommPacket::pType CommPacket::getPacketType()
{
    return packetType;
}

const char* CommPacket::getPacketName()
{
    return CommPacket::typeNames[ packetType ];
}

QDataStream& operator<<(QDataStream& ds, CommPacket& cr)
{
    return ds << (quint8&)cr.packetType;
}

QDataStream& operator>>(QDataStream& ds, CommPacket& cr)
{
    ds >> (quint8&)cr.packetType;

    if (cr.packetType >= CommPacket::typeNumber)
        cr.packetType  = CommPacket::UNKNOW;

    return ds;
}

const quint8 CommPacket::typeNumber = 8;

const char*  CommPacket::typeNames[] =
{
    "Unknow ",
    "Error ",
    "Init  ",
    "Alive ",
    "Login ",
    "File  ",
    "Config",
    "Module"
};

QDebug operator<<(QDebug d, CommPacket& cr)
{
    return d << cr.getPacketName();
}
