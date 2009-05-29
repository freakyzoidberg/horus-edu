#include "CommPacket.h"

CommPacket::CommPacket(Type _type)
{
    packetType = _type;
}

CommPacket::CommPacket(QByteArray& a)
{
    packetType = UNDEFINED;
    read(a);
}

const QByteArray CommPacket::getPacket() const
{
    QByteArray a;
    write(a);
    return a;
}

void CommPacket::read(QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        packetType = (Type)(char)a[0];
    a.remove(0,1);
}

void CommPacket::write(QByteArray& a) const
{
    a.append((char)packetType);
}

QDebug operator<<(QDebug d, const CommPacket& cr)
{
    static const char*  typeNames[] =
    {
        "Unknow ",
        "Error  ",
        "Init   ",
        "Alive  ",
        "Login  ",
        "File   ",
        "Setting",
        "Plugin "
    };
    return d << typeNames[ cr.packetType ] << '|';
}
