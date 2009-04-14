#include "CommPacket.h"

const quint8 CommPacket::typeNumber = 8;
const char*  CommPacket::typeNames[] =
{
    "Unknow",
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

CommPacket::CommPacket(QByteArray& a)
{
    packetType = a[0];
    if (packetType >= typeNumber)
        packetType = UNKNOW;
    a.remove(0,1);
}

QByteArray CommPacket::getPacket()
{
    return QByteArray(1, packetType);
}

QDebug operator<<(QDebug d, CommPacket& cr)
{
    return d << CommPacket::typeNames[ cr.packetType ] << '|';
}
