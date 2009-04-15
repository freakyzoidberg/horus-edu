#include "CommInit.h"

CommInit::CommInit(quint8 _protoVersion, const char* _fromName) : CommPacket(CommPacket::INIT)
{
    protoVersion = _protoVersion;
    fromName  = _fromName;
}

CommInit::CommInit(QByteArray& a) : CommPacket(CommPacket::INIT)
{
    protoVersion = a[0];
    a.remove(0, 1);
    fromName = a;
}

const QByteArray CommInit::getPacket()
{
    QByteArray a = CommPacket::getPacket();
    a.append(protoVersion);
    a.append(fromName);
    return a;
}

QDebug operator<<(QDebug d, CommInit& ci)
{
    return d << (CommPacket&)ci
             <<  "proto v:" << ci.protoVersion
             << " from:"    << ci.fromName;
}
