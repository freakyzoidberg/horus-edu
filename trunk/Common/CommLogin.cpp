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

CommLogin::CommLogin() : CommPacket(CommPacket::LOGIN)
{
    loginType  = UNDEFINED;
    login = "";
    sha1Pass = "";
    sessionString = "";
    sessionTime = 0;
}

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
}

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

QDebug operator<<(QDebug d, CommLogin& cl)
{
    d << (CommPacket&)cl;

    return d << CommLogin::typeMessages[ cl.loginType ]
             << cl.login
             << cl.sha1Pass.toHex()
             << cl.sessionString
             << cl.sessionTime;
}
