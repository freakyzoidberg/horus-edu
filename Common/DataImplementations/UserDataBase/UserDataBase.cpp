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
    Data::dataToStream(s);
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
    Data::dataFromStream(s);
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
//#include <QtSql>
void UserDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users WHERE id=?;");
    query.addBindValue(id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
    login      = query.value(0).toString();
    level      = (UserLevel)(query.value(1).toUInt());
    lastLogin  = query.value(2).toDateTime();
    surname    = query.value(3).toString();
    name       = query.value(4).toString();
    birthDate  = query.value(5).toDateTime();
    picture    = query.value(6).toByteArray();
    address    = query.value(7).toString();
    phone      = query.value(8).toString();
    country    = query.value(9).toString();
    language   = query.value(10).toString();
    idTree     = query.value(11).toUInt();
    enabled    = query.value(12).toBool();
    _lastChange= query.value(13).toDateTime();
}

void UserDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO users (login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
    query.addBindValue(login);
    query.addBindValue(level);
    query.addBindValue(lastLogin);
    query.addBindValue(surname);
    query.addBindValue(name);
    query.addBindValue(birthDate);
    query.addBindValue(picture);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(country);
    query.addBindValue(language);
    query.addBindValue(idTree);
    query.addBindValue(enabled);
    query.addBindValue(QDateTime::currentDateTime());
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
    id = query.lastInsertId().toUInt();
}

void UserDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE users SET login=?,level=?,last_login=?,surname=?,name=?,birth_date=?,picture=?,address=?,phone=?,country=?,language=?,id_tree=?,enabled=?,mtime=? WHERE id=?;");
    query.addBindValue(login);
    query.addBindValue(level);
    query.addBindValue(lastLogin);
    query.addBindValue(surname);
    query.addBindValue(name);
    query.addBindValue(birthDate);
    query.addBindValue(picture);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(country);
    query.addBindValue(language);
    query.addBindValue(idTree);
    query.addBindValue(enabled);
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(id);
    if ( ! query.exec())
    {
        qDebug() << query.lastError();
        _error = NOT_FOUND;
        return;
    }
}

void UserDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM users WHERE id=?;");
    query.addBindValue(id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
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

void UserDataBase::updateLastLogin(QSqlQuery& query)
{
    query.prepare("UPDATE users SET last_login=? WHERE id=?;");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}
#endif
