#include "UserDataBase.h"
#include "UserDataBasePlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"
#include "../../TreeDataPlugin.h"
#include <QIcon>

void UserDataBase::keyToStream(QDataStream& s)
{
    s << _id;
}

void UserDataBase::dataToStream(QDataStream& s)
{
    s << _level
      << _enabled
      << _login

      << _lastLogin
      << _surname
      << _name
      << _birthDate
      << _picture
      << _address
      << _phone
      << _country
      << _language;
    if (_node)
      s << _node->id();
    else
      s << 0;
    Data::dataToStream(s);
}

void UserDataBase::dataFromStream(QDataStream& s)
{
    quint32 nodeId;
    s >> _level
      >> _enabled
      >> _login

      >> _lastLogin
      >> _surname
      >> _name
      >> _birthDate
      >> _picture
      >> _address
      >> _phone
      >> _country
      >> _language
      >> nodeId;

    TreeDataPlugin* treePlugin = _plugin->pluginManager->findPlugin<TreeDataPlugin*>();
    if (treePlugin)
        _node = treePlugin->getNode(nodeId);
    else
        _node = 0;

    Data::dataFromStream(s);
}

QDebug UserDataBase::operator<<(QDebug debug) const
{
    return debug << getDataType()
                 << error()
                 << status()
                 << _id
                 << _level
                 //<< _enabled
                 << _login
                 << _lastLogin
                 //<< surname
                 //<< name
                 //<< birthDate
                 //<< picture
                 //<< address
                 //<< phone
                 //<< country
                 //<< language
                 ;
    if (_node)
        debug << _node->id();
}

void UserDataBase::setName(const QString name)
{
    if (_name == name)
        return;

    _name = name;
}

void UserDataBase::setSurname(const QString surname)
{
    if (_surname == surname)
        return;

    _surname = surname;
}

void UserDataBase::setLevel(quint8 level)
{
    if (_level == level)
        return;

    _level = level;
}

void UserDataBase::enable(bool enabled)
{
    if (_enabled == enabled)
        return;

    _enabled = enabled;
}

void UserDataBase::setNode(TreeData* node)
{
    if ( ! node || _node == node)
        return;

    _node = node;
}

void UserDataBase::setLanguage(const QString language)
{
    if (_language == language)
        return;

    _language = language;
}

void UserDataBase::setCountry(const QString country)
{
    if (_country == country)
        return;

    _country = country;
}

void UserDataBase::setPhone(const QString phone)
{
    if (_phone == phone)
        return;

    _phone = phone;
}

void UserDataBase::setAddress(const QString address)
{
    if (_address == address)
        return;

    _address = address;
}

void UserDataBase::setBirthDate(const QDate birthDate)
{
    if (_birthDate == birthDate)
        return;

    _birthDate = birthDate;
}

void UserDataBase::setPicture(const QByteArray picture)
{
    if (_picture == picture)
        return;

    _picture = picture;
}

#ifdef HORUS_CLIENT
QVariant UserDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return _id;
        if (column == 1)
            return _login;
        if (column == 2)
            return _name;
        if (column == 3)
            return _surname;
        if (column == 4)
            return _lastLogin;
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
       if (level() == 2)
            return QIcon(":/boss.ico");
        else
            return QIcon(":/user.ico");
    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
void UserDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users WHERE id=?;");
    query.addBindValue(_id);
    if ( ! query.exec() || ! query.next())
    {
//        _error = NOT_FOUND;
        return;
    }
    _login      = query.value(0).toString();
    _level      = (UserLevel)(query.value(1).toUInt());
    _lastLogin  = query.value(2).toDateTime();
    _surname    = query.value(3).toString();
    _name       = query.value(4).toString();
    _birthDate  = query.value(5).toDateTime();
    _picture    = query.value(6).toByteArray();
    _address    = query.value(7).toString();
    _phone      = query.value(8).toString();
    _country    = query.value(9).toString();
    _language   = query.value(10).toString();
    TreeDataPlugin* treePlugin = _plugin->pluginManager->findPlugin<TreeDataPlugin*>();
    if (treePlugin)
        _node = treePlugin->getNode( query.value(11).toUInt() );
    else
        _node = 0;
    _enabled    = query.value(12).toBool();
    _lastChange= query.value(13).toDateTime();
}

void UserDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO users (login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime,password) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
    query.addBindValue(_login);
    query.addBindValue(_level);
    query.addBindValue(_lastLogin);
    query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue(_language);
    if (_node)
        query.addBindValue(_node->id());
    else
        query.addBindValue(0);
    query.addBindValue(_enabled);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);

    query.addBindValue("7c4a8d09ca3762af61e59520943dc26494f8941b");

    query.exec();
//    if ( ! query.exec() || ! query.next())
//    {
//        qDebug() << "createIntoDatabase error";
//        _error = DATABASE_ERROR;
//        return;
//    }
//    _id = query.lastInsertId().toUInt();

    quint32 newId = query.lastInsertId().toUInt();

    query.prepare("UPDATE users SET id=? WHERE id=?;");
    query.addBindValue(_id);
    query.addBindValue(newId);
    query.exec();

}

void UserDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE users SET login=?,level=?,last_login=?,surname=?,name=?,birth_date=?,picture=?,address=?,phone=?,country=?,language=?,id_tree=?,enabled=?,mtime=? WHERE id=?;");
    query.addBindValue(_login);
    query.addBindValue(_level);
    query.addBindValue(_lastLogin);
    query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue("vide");
    query.addBindValue(_language);
    if (_node)
        query.addBindValue(_node->id());
    else
        query.addBindValue(0);
    query.addBindValue(_enabled);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    query.addBindValue(_id);
    query.exec();

    if (query.numRowsAffected() <= 0)
        createIntoDatabase(query);
//    else if ( ! query.exec())
//    {
//        qDebug() << query.lastError();
//        _error = NOT_FOUND;
//        return;
//    }
}

void UserDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM users WHERE id=?;");
    query.addBindValue(_id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

QByteArray UserDataBase::newSession(QSqlQuery& query, const QDateTime& end)
{
    QByteArray session;
    qsrand(QTime::currentTime().msec() + _id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    query.prepare("UPDATE users SET session_key=?, session_end=? WHERE id=?;");
    query.addBindValue(session.toHex());
    query.addBindValue(end);
    query.addBindValue(_id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;

    return session;
}

void UserDataBase::destroySession(QSqlQuery& query)
{
    query.prepare("UPDATE users SET session_key='', session_end='' WHERE id=?;");
    query.addBindValue(_id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}

void UserDataBase::updateLastLogin(QSqlQuery& query)
{
    query.prepare("UPDATE users SET last_login=? WHERE id=?;");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(_id);
    if ( ! query.exec())
        _error = DATABASE_ERROR;
}
#endif
