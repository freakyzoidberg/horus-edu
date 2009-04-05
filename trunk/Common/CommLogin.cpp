#include "CommLogin.h"

CommLogin::CommLogin(CommMiniString _login)
{
    clientProtoVersion = CURRENT_PROTO_VERSION;
    clientName  = CLIENT_NAME;
    clientName += " Ver. ";
    clientName += CLIENT_VERSION;
    login = _login;
    type = HASH_MD5;
}

QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    ds << cl.clientProtoVersion;
    ds << cl.clientName;
    ds << cl.login;
    ds << (quint8&)cl.type;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> cl.clientProtoVersion;
    ds >> cl.clientName;
    ds >> cl.login;
    ds >> (quint8&)cl.type;
    return ds;
}
