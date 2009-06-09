#include "CommPacket.h"

CommPacket::CommPacket(Type _type)
{
    packetType = _type;
}

CommPacket::CommPacket(const QByteArray& a)
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

void CommPacket::read(const QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        packetType = (Type)(char)a[0];
}

void CommPacket::write(QByteArray& a) const
{
    a = QByteArray(1,(char)packetType);
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
