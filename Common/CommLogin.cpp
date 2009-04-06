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
    qDebug() << "-[out Login ]" << cl;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> (quint8&)cl.type;
    ds >> cl.login;
    qDebug() << "-[ in Login ]" << cl;
    return ds;
}

QDebug operator<<(QDebug d, CommLogin& cl)
{
    return d << " type ="  << cl.type
             << " login =" << cl.login;
}
