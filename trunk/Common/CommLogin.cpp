#include "CommLogin.h"

CommLogin::CommLogin(CommMiniString _clientVersion, CommMiniString _login, authType _type)
{
    clientVersion = _clientVersion;
    login = _login;
    type = _type;
}

QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    ds << cl.clientVersion;
    ds << cl.login;
    ds << (quint8&)cl.type;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> cl.clientVersion;
    ds >> cl.login;
    ds >> (quint8&)cl.type;
    return ds;
}
