#include "CommInit.h"

CommInit::CommInit()
{
}

CommInit::CommInit(quint8 _protoVersion, const char* _fromName)
{
    protoVersion = _protoVersion;
    fromName  = _fromName;
}

QDataStream& operator<<(QDataStream& ds, CommInit& ci)
{
    ds << ci.protoVersion;
    ds << ci.fromName;
    qDebug() << "[out CommInit]" << ci;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommInit& ci)
{
    ds >> ci.protoVersion;
    ds >> ci.fromName;
    qDebug() << "[ in CommInit]" << ci;
    return ds;
}

QDebug operator<<(QDebug d, CommInit& ci)
{
    return d <<  "protoVersion =" << ci.protoVersion
             << " fromName ="         << ci.fromName;
}
