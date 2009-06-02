#include "CommLogin.h"
#include <QDateTime>
#include <QtEndian>
#include <QVariant>

CommLogin::CommLogin(Method t) : CommPacket(CommPacket::LOGIN)
{
    method  = t;
    login = "";
    sha1Pass = "";
    sessionTime = 0;
    sessionString = "";
}

CommLogin::CommLogin(QByteArray& a) : CommPacket(CommPacket::LOGIN)
{
    login = "";
    level = LEVEL_GUEST;
    sha1Pass = "";
    sessionTime = 0;
    sessionString = "";
    read(a);
}

const QByteArray CommLogin::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommLogin::read(QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        method = (Method)(char)a[0];
    a.remove(0,1);

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        login = a.mid(1, a[0]);
        a.remove(0, a[0] + 1);
        if (method == LOGIN_PASSWORD)
            sha1Pass = a;
        else
            sessionString = a;
    }
    else if (method == ACCEPTED)
    {
        if ((char)a[0] < (char)__LAST_LEVEL__)
            level = (UserLevel)(char)a[0];

        sessionTime = QVariant(a.mid(1, a[1])).toUInt();
        a.remove(0, a[1]+2);
        sessionString = a;
    }
}

void CommLogin::write(QByteArray& a) const
{
    a.append(method);

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        a.append(login.length());
        a.append(login);
        if (method == LOGIN_PASSWORD)
            a.append(sha1Pass);
        else
            a.append(sessionString);
    }
    else if (method == ACCEPTED)
    {
        a.append((char)level);
        QByteArray time = QVariant(sessionTime).toByteArray();
        a.append(time.length());
        a.append(time);
        a.append(sessionString);
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
        "Refused      "
    };

    d << (CommPacket&)cl
      << typeMessages[ cl.method ];

    if (cl.method == CommLogin::ACCEPTED)
        d << cl.level
          << cl.sessionString.toHex()
          << cl.sessionTime;

    else if (cl.method == CommLogin::LOGIN_PASSWORD)
        d << cl.login
          << cl.sha1Pass.toHex();

    else if (cl.method == CommLogin::LOGIN_SESSION)
        d << cl.login
          << cl.sessionString.toHex();

    return d;
}
