#include "CommPacket.h"

CommPacket::CommPacket(msgType _type)
{
    type = _type;
}

QDataStream& operator<<(QDataStream& ds, CommPacket& cr)
{
    ds << (quint8&)cr.type;
    qDebug() << "[out CommPacket]" << cr;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommPacket& cr)
{
    ds >> (quint8&)cr.type;
    qDebug() << "[ in CommPacket]" << cr;
    return ds;
}

const quint8 CommPacket::typeNumber = 6;
const char*  CommPacket::typeMessages[] =
{
    "Unknow protocol",
    "Alive",
    "Login",
    "File",
    "Config",
    "Module"
};

QDebug operator<<(QDebug d, CommPacket& cr)
{
    quint8 t = cr.type;
    if (t >= CommPacket::typeNumber)
        t = CommPacket::UNKNOW_PROTOCOL;

    return d << "type =" << t << CommPacket::typeMessages[ t ];
}
