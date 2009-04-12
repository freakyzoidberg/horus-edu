#include "CommInit.h"

CommInit::CommInit() : CommPacket(CommPacket::INIT)
{
    protoVersion = 0;
    fromName  = "";
}

CommInit::CommInit(quint8 _protoVersion, const char* _fromName) : CommPacket(CommPacket::INIT)
{
    protoVersion = _protoVersion;
    fromName  = _fromName;
}

QDataStream& operator<<(QDataStream& ds, CommInit& ci)
{
    qDebug() << "[out]" << ci;
    return ds << (CommPacket&)ci << ci.protoVersion << ci.fromName;
}

QDataStream& operator>>(QDataStream& ds, CommInit& ci)
{
    ds >> ci.protoVersion >> ci.fromName;
    qDebug() << "[ in]" << ci;
    return ds;
}

QDebug operator<<(QDebug d, CommInit& ci)
{
    return d << (CommPacket&)ci
             <<  "proto v:" << ci.protoVersion
             << " from:"    << ci.fromName;
}
