#include "User.h"

User::User()
{
    id = 0;
    login = "";
    session = "";
}


bool User::loginPassword(const QByteArray& _login, const QByteArray& _sha1Pass)
{
    if (_sha1Pass.length() != 20 || _login.length() > 32)
        return false;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("SELECT id FROM users WHERE login=? AND password=? LIMIT 1;");
    query.addBindValue(_login);
    query.addBindValue(_sha1Pass.toHex());
    if ( ! query.exec() || ! query.next())
    {
        id = 0;
        login = "";
        session = "";
        qDebug() << login << " bad user or password.";
        return false;
    }

    id = query.value(0).toUInt();
    login =_login;
    qDebug() << login << " logged in.";
    return true;
}

bool User::loginSession(const QByteArray& _login, const QByteArray& _sessId)
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
