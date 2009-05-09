#include "CommPacket.h"

CommPacket::CommPacket(pType _type)
{
    packetType = _type;
}

CommPacket::CommPacket(QByteArray& a)
{
    read(a);
}

const QByteArray CommPacket::getPacket()
{
    QByteArray a;
    write(a);
    return a;
}

void CommPacket::read(QByteArray& a)
{
    quint8 t = a[0];
    if (t >= __LAST__)
        packetType = UNDEFINED;
    else
        packetType = (pType)t;
    a.remove(0,1);
}

void CommPacket::write(QByteArray& a)
{
    a.append((char)packetType);
}

QDebug operator<<(QDebug d, CommPacket& cr)
{
    static const char*  typeNames[] =
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
    return d << typeNames[ cr.packetType ] << '|';
}
