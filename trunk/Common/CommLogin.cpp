#include "CommLogin.h"

CommLogin::CommLogin(packetType _type, CommMiniString _login)
{
    type  = _type;
    login = _login;
}

QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    ds << (quint8&)cl.type;
    ds << cl.login;
    qDebug() << "->[out Login ]" << cl;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> (quint8&)cl.type;
    ds >> cl.login;
    qDebug() << "->[ in Login ]" << cl;
    return ds;
}

const quint8 CommLogin::typeNumber = 5;
const char*  CommLogin::typeMessages[] =
{
    "Error",
    "Login",
    "Logout",
    "Accepted",
    "Refused"
};

QDebug operator<<(QDebug d, CommLogin& cl)
{
    quint8 t = cl.type;
    if (t >= CommLogin::typeNumber)
        t = CommLogin::ERROR;

    return d << "type =" << CommLogin::typeMessages[ t ]
             << " login =" << cl.login;
}
