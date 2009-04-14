#include "CommLogin.h"

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

    login = "";
    sha1Pass = "";
    sessionTime = 0;
    sessionString = "";

    if (loginType == LOGIN_PASSWORD || loginType == LOGIN_SESSION)
    {
        login = a.mid(2, a[1]);
        //qDebug() << login;
        a.remove(0, a[1] + 2);
        if (loginType == LOGIN_PASSWORD)
            sha1Pass = a;
        else
            sessionString = a;
    }
    else if (loginType == ACCEPTED)
    {
        sessionTime = *(a.mid(1, sizeof(sessionTime)).data());
        sessionString = a;
    }
    else if (loginType != LOGOUT && loginType != REFUSED)
        loginType = UNKNOW;
}

QByteArray CommLogin::getPacket()
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
        a.append((const char*)&sessionTime, sizeof(sessionTime));
        a.append(sessionString);
    }
    return a;
 }

/*
bool CommLogin::isValidContent()
{
    if (loginType == REFUSED
        || loginType == LOGOUT
        || (loginType == ACCEPTED
             && sessionString.length() == SESSION_WORD_SIZE
             && sessionTime > 0)
        || (loginType == LOGIN_PASSWORD
            && ! login.isEmpty()
            && sha1Pass.length() == SHA1_WORD_SIZE)
        || (loginType == LOGIN_SESSION
            && ! login.isEmpty()
            && sessionString.length() == SESSION_WORD_SIZE)
        )
        return true;

    qCritical() << "Invalid login packet" << *this;
    return false;
}*/
/*
QDataStream& operator<<(QDataStream& ds, CommLogin& cl)
{
    if ( ! cl.isValidContent())
        return ds;

    qDebug() << "[out]" << cl;
    return ds << (CommPacket&)cl << (quint8&)cl.loginType << cl.login << cl.sha1Pass << cl.sessionString << cl.sessionTime;
}

QDataStream& operator>>(QDataStream& ds, CommLogin& cl)
{
    ds >> (quint8&)cl.loginType;

    if (cl.loginType >= CommLogin::typeNumber)
        cl.loginType  = CommLogin::UNDEFINED;

    ds >> cl.login >> cl.sha1Pass >> cl.sessionString >> cl.sessionTime;
    qDebug() << "[ in]" << cl;
    return ds;
}
*/
QDebug operator<<(QDebug d, CommLogin& cl)
{
    d << (CommPacket&)cl;

    return d << CommLogin::typeMessages[ cl.loginType ]
             << cl.login
             << cl.sha1Pass.toHex()
             << cl.sessionString.toHex()
             << cl.sessionTime;
}
