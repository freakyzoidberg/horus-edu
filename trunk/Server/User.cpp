#include "User.h"
#include "Sql.h"
#include "../Common/CommModule.h"

QMap<quint32, User*> User::map;

User::User(ClientSocket* sock)
{
    socket = sock;
    id = 0;
    user = "";
    session = "";
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
        query.prepare("SELECT id FROM users WHERE login=? AND session_key=? LIMIT 1;");
    else
        query.prepare("SELECT id FROM users WHERE login=? AND password=? LIMIT 1;");

    query.addBindValue(_login);
    query.addBindValue(_auth.toHex());
    if ( ! query.exec() || ! query.next())
        return;

    id = query.value(0).toUInt();
    user = _login;

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec() + id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    query.clear();
    query.prepare("UPDATE users SET session_key=? WHERE id=? LIMIT 1;");
    query.addBindValue(session.toHex());
    query.addBindValue(id);
    if ( ! query.exec())
        return;

    connect(this, SIGNAL(sendPacketSignal(const QByteArray&)), socket, SLOT(sendPacket(const QByteArray&)));

    qDebug() << user << id << session.toHex() << "connected";

    map[ id ] = this;
    socket->userId = id;
    return;
}

const QByteArray& User::getSession()
{
    return session;
}

void User::sendPacket(const QByteArray& packet)
{
    emit sendPacketSignal(packet);
}

User* User::getUser(quint32 _id)
{
    return map[ _id ];
}


/*
void User::destroySession()
{
    QMutexLocker lock(&mutex);

    id = 0;
    login = "";
    session = "";
    state = LOGGED_OUT;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE users SET session_key='' WHERE id=? LIMIT 1;");
    query.addBindValue(id);
    query.exec();
}
*/
