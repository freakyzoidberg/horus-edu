#include "User.h"

User::User()
{
    login = "";
    session = "";
}


bool User::loginPassword(const QString& _login, const QByteArray& _sha1Pass)
{
    QByteArray hash = QCryptographicHash::hash("toto42", QCryptographicHash::Sha1);

    //if (_login != "toto42")

      //  && _sha1Pass == hash)
    return false;
}

bool User::loginSession(const QString& _login, const QByteArray& _sessId)
{
    return false;
}

void User::logout()
{
    login = "";
    session = "";
    //Also delete session string in the database
    //socket.disconnectFromHost();
}


const QByteArray& User::getSession()
{
    return session;
}
