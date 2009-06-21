#include "CommLogin.h"
#include <QDateTime>
#include <QtEndian>
#include <QVariant>
#include <QDataStream>

CommLogin::CommLogin(Method t) : CommPacket(CommPacket::LOGIN)
{
    method  = t;
    level = LEVEL_GUEST;
    sessionTime = 0;
}

CommLogin::CommLogin(const QByteArray& a) : CommPacket(CommPacket::LOGIN)
{
    method  = UNDEFINED;
    level = LEVEL_GUEST;
    sessionTime = 0;
    read(a);
}

const QByteArray CommLogin::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommLogin::read(const QByteArray& a)
{
    QDataStream stream(a);
    stream.device()->seek( lenParent() );

    stream >> (quint8&)method;
    if (method >= __LAST__)
        method = UNDEFINED;

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        stream >> login;
        if (method == LOGIN_PASSWORD)
            stream >> password;
        else
            stream >> sessionString;
    }
    else if (method == ACCEPTED)
    {
        stream >> (quint8&)level;
        if (level >= __LAST_LEVEL__)
            level = LEVEL_GUEST;

        stream >> sessionTime;
        stream >> sessionString;
    }
}

void CommLogin::write(QByteArray& a) const
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek( lenParent() );

    stream << (quint8)method;

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        stream << login;
        if (method == LOGIN_PASSWORD)
            stream << password;
        else
            stream << sessionString;
    }
    else if (method == ACCEPTED)
    {
        stream << (quint8)level;
        stream << sessionTime;
        stream << sessionString;
    }
 }

QDebug operator<<(QDebug d, const CommLogin& cl)
{
    static const char*  typeMessages[] =
    {
        "Undefined    ",
        "Login Pass   ",
        "Login Session",
        "Logout       ",
        "Accepted     ",
        "Refused      ",
        "Disconnected "
    };

    d << (CommPacket&)cl
      << typeMessages[ cl.method ];

    if (cl.method == CommLogin::ACCEPTED)
        d << cl.level
          << cl.sessionString.toHex()
          << cl.sessionTime;

    else if (cl.method == CommLogin::LOGIN_PASSWORD)
        d << cl.login
          << cl.password.toHex();

    else if (cl.method == CommLogin::LOGIN_SESSION)
        d << cl.login
          << cl.sessionString.toHex();

    return d;
}
