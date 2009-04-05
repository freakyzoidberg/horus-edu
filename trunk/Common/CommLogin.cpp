#include "CommLogin.h"

CommLogin::CommLogin(const char* _cliVersion, const char* _login, authType _type)
{
    cliVersion = _cliVersion;
    login = _login;
    type = _type;
}

QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    ds << cl.cliVersion;
    ds << cl.login;
    ds << (quint8)cl.type;
    return ds;
}
