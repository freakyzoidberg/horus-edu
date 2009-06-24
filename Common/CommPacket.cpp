#include "CommPacket.h"
#include "CommData.h"
#include "CommError.h"
#include "CommInit.h"
#include "CommLogin.h"
#include "CommPlugin.h"

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
        "Data   ",
        "Plugin "
    };
    return d << typeNames[ cr.packetType ] << '|';
}

void CommPacket::debugPacket(QDebug d, const QByteArray& src)
{
    CommPacket packet(src);
    if (packet.packetType == CommPacket::DATA)
        d << CommData(src);
    else if (packet.packetType == CommPacket::ERROR)
        d << CommError(src);
    else if (packet.packetType == CommPacket::INIT)
        d << CommInit(src);
    else if (packet.packetType == CommPacket::LOGIN)
        d << CommLogin(src);
    else if (packet.packetType == CommPacket::PLUGIN)
        d << CommPlugin(src);
    else
        d << packet;
}
