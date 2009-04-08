#include "CommLogin.h"

CommLogin::CommLogin(packetType _type, CommMiniString _login) : CommPacket(CommPacket::LOGIN)
{
    type  = _type;
    login = _login;
}

QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    qDebug() << "[out]" << cl;
    return ds << (CommPacket&)cl << (quint8&)cl.type << cl.login;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> (quint8&)cl.type >> cl.login;
    qDebug() << "[ in]" << cl;
    return ds;
}

const quint8 CommLogin::typeNumber = 5;
const char*  CommLogin::typeMessages[] =
{
    "Error",
    "Login",
    "Logout",
    "Accepted",
    "Refused "
};

QDebug operator<<(QDebug d, CommLogin& cl)
{
    d << (CommPacket&)cl;

    quint8 t = cl.type;
    if (t >= CommLogin::typeNumber)
        t = CommLogin::ERROR;

    return d << CommLogin::typeMessages[ t ]
             << cl.login;
}
