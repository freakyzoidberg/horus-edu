#include "CommPacket.h"

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

CommPacket::CommPacket(type _type)
{
    packetType = _type;
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

QDebug operator<<(QDebug d, CommPacket& cr)
{
    return d << CommPacket::typeNames[ cr.packetType ] << '|';
}
