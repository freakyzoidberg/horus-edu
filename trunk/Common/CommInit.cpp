#include "CommInit.h"

CommInit::CommInit()
{
    serverProtoVersion = CURRENT_PROTO_VERSION;
    serverName  = SERVER_NAME;
    serverName += " Ver. ";
    serverName += SERVER_VERSION;
}

QDataStream& operator<<(QDataStream& ds, CommInit& ci)
{
    ds << ci.serverProtoVersion;
    ds << ci.serverName;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommInit& ci)
{
    ds >> ci.serverProtoVersion;
    ds >> ci.serverName;
    return ds;
}
