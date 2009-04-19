#include "CommLogin.h"
#include <QDateTime>
#include <QtEndian>

const quint8 CommLogin::typeNumber = 6;
const char*  CommLogin::typeMessages[] =
{
    "Undefined",
    "Login Pass",
    "Login Session",
    "Logout",
    "Accepted",
    "Refused"
};

CommLogin::CommLogin(lType t) : CommPacket(CommPacket::LOGIN)
{
    loginType  = t;
    login = "";
    sha1Pass = "";
    sessionTime = 0;
    sessionString = "";
}

CommLogin::CommLogin(QByteArray& a) : CommPacket(CommPacket::LOGIN)
{
    loginType = a[0];
    a.remove(0, 1);

    login = "";
    sha1Pass = "";
    sessionTime = 0;
    sessionString = "";

    if (loginType == LOGIN_PASSWORD || loginType == LOGIN_SESSION)
    {
        login = a.mid(1, a[0]);
        a.remove(0, a[0] + 1);
        if (loginType == LOGIN_PASSWORD)
            sha1Pass = a;
        else
            sessionString = a;
    }
    else if (loginType == ACCEPTED)
    {
        sessionString = a;
        memcpy((char*)&sessionTime, a.constData(), sizeof(sessionTime));
        sessionTime = qFromLittleEndian(sessionTime);
        a.remove(0, sizeof(sessionTime));
    }
    else if (loginType != DESTROY_SESSION && loginType != REFUSED)
        loginType = UNKNOW;
}

const QByteArray CommLogin::getPacket()
{
    QByteArray a = CommPacket::getPacket();

    a.append(loginType);

    if (loginType == LOGIN_PASSWORD || loginType == LOGIN_SESSION)
    {
        a.append(login.length());
        a.append(login);
        if (loginType == LOGIN_PASSWORD)
            a.append(sha1Pass);
        else
            a.append(sessionString);
    }
    else if (loginType == ACCEPTED)
    {
        quint32 time = qToLittleEndian(sessionTime);
        a.append((char*)&time, sizeof(sessionTime) );
        a.append(sessionString);
    }
    return a;
 }

QDebug operator<<(QDebug d, CommLogin& cl)
{
    d << (CommPacket&)cl;

    return d << CommLogin::typeMessages[ cl.loginType ]
             << cl.login
             << cl.sha1Pass.toHex()
             << cl.sessionString.toHex()
             << cl.sessionTime;
}
