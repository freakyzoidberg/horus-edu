#include "UserDataBase.h"
#include "UserDataBasePlugin.h"

void UserDataBase::keyToStream(QDataStream& s)
{
    s << (quint32)id;
}

void UserDataBase::dataToStream(QDataStream& s)
{
    s << (quint8)level
      << (bool)enabled
      << login

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

void UserDataBase::dataFromStream(QDataStream& s)
{
    s >> (quint8&)level
      >> (bool&)enabled
      >> login

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

QDebug UserDataBase::operator<<(QDebug debug) const
{
    return debug << getDataType()
                 << error()
                 << id
                 << level
                 //<< enabled
                 << login
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
QVariant UserDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return id;
        if (column == 1)
            return login;
        if (column == 2)
            return name;
        if (column == 3)
            return surname;
        if (column == 4)
            return lastLogin;
    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
void UserDataBase::fillFromDatabase(QSqlQuery& query)
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

void UserDataBase::createIntoDatabase(QSqlQuery& TODO)
{
}

void UserDataBase::saveIntoDatabase  (QSqlQuery& TODO)
{
}

void UserDataBase::deleteFromDatabase(QSqlQuery& TODO)
{
}

QByteArray UserDataBase::newSession(QSqlQuery& query, const QDateTime& end)
{
     //TODO maybe change this value
    QByteArray session;
    qsrand(QTime::currentTime().msec() + id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    query.prepare("UPDATE users SET session_key=?, session_end=? WHERE id=?;");
    query.addBindValue(session.toHex());
    query.addBindValue(end);
    query.addBindValue(id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;

    return session;
}

void UserDataBase::destroySession(QSqlQuery& query)
{
    query.prepare("UPDATE users SET session_key='', session_end='' WHERE id=?;");
    query.addBindValue(id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}

#endif
