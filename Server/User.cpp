#include "User.h"

User::User()
{
    state = INIT;
}

User::~User()
{
    if (state == LOGGED_IN)
        qDebug() << login << "disconnected";
    //here socket is already disconected
}

void User::init()
{
    QMutexLocker lock(&mutex);
    id = 0;
    login = "";
    session = "";
    state = LOGGED_OUT;
}

bool User::loginPassword(const QByteArray& _login, const QByteArray& _sha1Pass)
{
    QMutexLocker lock(&mutex);
    if (state != LOGGED_OUT)
        return false;

    if (_sha1Pass.length() != SHA1_WORD_SIZE || _login.length() > 32)
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
        qDebug() << _login << " bad user or password.";
        return false;
    }

    id = query.value(0).toUInt();
    login = _login;
    state = LOGGED_IN;
    qDebug() << login << " logged in.";

    return true;
}

bool User::loginSession(const QByteArray& _login, const QByteArray& _sessId)
{
    QMutexLocker lock(&mutex);
    if (state != LOGGED_OUT)
        return false;

    if (_sessId.length() != SESSION_WORD_SIZE || _login.length() > 32)
        return false;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("SELECT id FROM users WHERE login=? AND session_key=? LIMIT 1;");
    query.addBindValue(_login);
    query.addBindValue(_sessId.toHex());
    if ( ! query.exec() || ! query.next())
    {
        id = 0;
        login = "";
        session = "";
        qDebug() << _login << " bad user or session";
        return false;
    }

    id = query.value(0).toUInt();
    login = _login;
    state = LOGGED_IN;
    qDebug() << login << " logged in.";

    return true;
}

void User::logout()
{
    init();
//    QMutexLocker(&mutex);
    //Also delete session string in the database
    //socket.disconnectFromHost();
}

User::tState User::getState()
{
    QMutexLocker lock(&mutex);
    return state;
}

const QByteArray& User::newSession()
{
    QMutexLocker lock(&mutex);

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec() + id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE users SET session_key=? WHERE id=? LIMIT 1;");
    query.addBindValue(session.toHex());
    query.addBindValue(id);
    if (query.exec())
        return session;
    session = "";
    return session;
}
