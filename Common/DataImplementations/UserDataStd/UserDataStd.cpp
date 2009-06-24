#include "UserDataStd.h"
#include "UserDataStdPlugin.h"

void UserDataStd::keyToStream(QDataStream& s)
{
    s << id;
}

void UserDataStd::dataToStream(QDataStream& s)
{
    s << level
      << enabled
      << login
      << session
      << sessionEnd
      << lastLogin
      << surname
      << name
      << birthDate
      << picture
      << address
      << phone
      << country
      << language
      << idTree;
}

void UserDataStd::dataFromStream(QDataStream& s)
{
    s >> (quint8&)level
      >> enabled
      >> login
      >> session
      >> sessionEnd
      >> lastLogin
      >> surname
      >> name
      >> birthDate
      >> picture
      >> address
      >> phone
      >> country
      >> language
      >> idTree;
}

QDebug UserDataStd::operator<<(QDebug debug) const
{
    return debug << getDataType()
                 << level
                 //<< enabled
                 << "login=" << login
                 //<< session.toHex()
                 //<< sessionEnd
                 << lastLogin
                 //<< surname
                 //<< name
                 //<< birthDate
                 //<< picture
                 //<< address
                 //<< phone
                 //<< country
                 //<< language
                 << idTree;
}

#ifdef HORUS_CLIENT
QVariant UserDataStd::getValue(int column, int role) const
{
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
void UserDataStd::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled FROM users WHERE id=?;");
    query.addBindValue(id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
    login      = query.value(0).toString();
    level      = (UserLevel)(query.value(1).toUInt());
    lastLogin = query.value(2).toDateTime();
    surname    = query.value(3).toString();
    name       = query.value(4).toString();
    birthDate = query.value(5).toDateTime();
//    picture    = query.value(6).to;
    address    = query.value(7).toString();
    phone      = query.value(8).toString();
    country    = query.value(9).toString();
    language   = query.value(10).toString();
    idTree    = query.value(11).toUInt();
    enabled    = query.value(12).toBool();
}

void UserDataStd::createIntoDatabase(QSqlQuery& TODO)
{
}

void UserDataStd::saveIntoDatabase  (QSqlQuery& TODO)
{
}

void UserDataStd::deleteFromDatabase(QSqlQuery& TODO)
{
}

void UserDataStd::newSession(QSqlQuery& query)
{
     sessionEnd = QDateTime::currentDateTime().addSecs( DEFAULT_SESSION_LIFETIME * 60 );

     //TODO maybe change this value
    qsrand(QTime::currentTime().msec() + id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    query.prepare("UPDATE users SET session_key=?, session_end=? WHERE id=?;");
    query.addBindValue(session.toHex());
    query.addBindValue(sessionEnd);
    query.addBindValue(id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}

void UserDataStd::destroySession(QSqlQuery& query)
{
    query.prepare("UPDATE users SET session_key='', session_end='' WHERE id=?;");
    query.addBindValue(id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}

#endif
