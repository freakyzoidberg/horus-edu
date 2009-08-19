#include "User.h"
#include "Sql.h"
#include "../Common/CommPlugin.h"

QHash<quint32, User*> User::loggedIn;

User::User()
{
    init();
}

void User::init()
{
    id = 0;
    user = "";
    sessionString = "";
}

User::~User()
{
    //here socket is already disconected
}

void User::login(const QString& _login, bool authSession, const QByteArray& _auth)
{
    if (_login.length() > 32
        || (   authSession && _auth.length() != SESSION_WORD_SIZE)
        || ( ! authSession && _auth.length() != SHA1_WORD_SIZE)
       )
        return;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    if (authSession)
        query.prepare("SELECT id,level FROM users WHERE enabled=1 AND login=? AND session_key=?;");
    else
        query.prepare("SELECT id,level FROM users WHERE enabled=1 AND login=? AND password=?;");

    query.addBindValue(_login);
    query.addBindValue(_auth.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "ERROR while logging in, either user/session not found or sql error";
        qDebug() << query.lastError().text();
        return;
    }

    id = query.value(0).toUInt();
    level = (UserLevel)query.value(1).toUInt();
    user = _login;

    loggedIn[ id ] = this;
}

void User::renewSession(quint32 duration)
{
    QDateTime end = QDateTime::currentDateTime().addSecs(duration);

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec() + id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        sessionString[i] = qrand();

    query.clear();
    query.prepare("UPDATE users SET session_key=?, session_end=? WHERE id=?;");
    query.addBindValue(sessionString.toHex());
    query.addBindValue(end.toTime_t());
    query.addBindValue(id);
    if ( ! query.exec())
        return;

    sessionEnd = end;

    return;
}

const QByteArray& User::getSessionString() const
{
    return sessionString;
}

const QDateTime& User::getSessionEnd() const
{
    return sessionEnd;
}

bool User::isLoggedIn() const { return loggedIn.contains(id); }
quint32 User::getId() const { return id; }
const QString User::getUserName() const { return user; }
UserLevel User::getLevel() const { return level; }

void User::sendPacket(const QByteArray& packet) const
{
    emit sendPacketSignal(packet);
}

User* User::getUser(quint32 _id)
{
    return loggedIn[ _id ];
}

void User::logout()
{
    if (isLoggedIn())
    {
        Sql con;
        QSqlQuery query(QSqlDatabase::database(con));
        query.prepare("UPDATE users SET session_key=NULL WHERE id=? LIMIT 1;");
        query.addBindValue(id);
        query.exec();
        loggedIn.remove(id);
    }
    init();
}