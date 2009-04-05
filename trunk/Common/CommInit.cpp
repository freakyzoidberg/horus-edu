#include "CommInit.h"

CommInit::CommInit(CommMiniString ver)
{
    serverName = "Horus Server";
    serverVersion = ver;
}

QDataStream& operator<<(QDataStream& ds, CommInit& ci)
{
    ds << ci.serverName;
    ds << ci.serverVersion;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommInit& ci)
{
    ds >> ci.serverName;
    ds >> ci.serverVersion;
    return ds;
}
