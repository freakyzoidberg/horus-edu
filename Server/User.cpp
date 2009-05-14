#include <QTime>

#include "User.h"
#include "Sql.h"
#include "../Common/CommModule.h"

QHash<quint32, User*> User::map;

User::User()
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
        query.prepare("SELECT id,level FROM users WHERE login=? AND session_key=?;");
    else
        query.prepare("SELECT id,level FROM users WHERE login=? AND password=?;");

    query.addBindValue(_login);
    query.addBindValue(_auth.toHex());
    if ( ! query.exec() || ! query.next())
        return;

    id = query.value(0).toUInt();
    level = (Level)query.value(1).toUInt();
    user = _login;

    map[ id ] = this;
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

bool User::isLoggedIn() const { return id ? true : false; }
quint32 User::getId() const { return id; }
const QString User::getUserName() const { return user; }
User::Level User::getLevel() const { return level; }

void User::sendPacket(const QByteArray& packet)
{
    emit sendPacketSignal(packet);
}

User* User::getUser(quint32 _id)
{
    return map[ _id ];
}

void User::destroySession()
{
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE users SET session_key='' WHERE id=? LIMIT 1;");
    query.addBindValue(id);
    query.exec();

    sessionString = "";
}

void User::logout()
{
    id = 0;
    user = "";
    sessionString = "";
}
