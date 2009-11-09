#include "UserDataBase.h"
#include "UserDataBasePlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"
#include "../../TreeDataPlugin.h"
#include <QCryptographicHash>

UserDataBase::UserDataBase(quint32 userId, UserDataBasePlugin* plugin) : UserData(userId, plugin)
{
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_node, SIGNAL(removed()), this, SLOT(nodeRemoved()));
}

void UserDataBase::nodeRemoved()
{
	disconnect(this, SLOT(nodeRemoved()));
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_node, SIGNAL(removed()), this, SLOT(nodeRemoved()));
}

void UserDataBase::keyToStream(QDataStream& s)
{
    s << _id;
}

void UserDataBase::dataToStream(QDataStream& s) const
{
    s << _level
      << _enabled
      << _login
	  << _password

      << _lastLogin
      << _surname
      << _name
      << _birthDate
      << _picture
      << _address
      << _phone
      << _country
	  << _language
	  << _node->id();

	Data::dataToStream(s);
}

void UserDataBase::dataFromStream(QDataStream& s)
{
    quint32 nodeId;
    s >> _level
      >> _enabled
      >> _login
	  >> _password

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

	disconnect(this, SLOT(nodeRemoved()));
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);
	connect(_node, SIGNAL(removed()), this, SLOT(nodeRemoved()));

    Data::dataFromStream(s);
}

QDebug UserDataBase::operator<<(QDebug debug) const
{
    return debug << dataType()
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
}

void UserDataBase::setName(const QString name)
{
	QMutexLocker M(&_mutex);
	if (_name == name)
        return;

    _name = name;
}

void UserDataBase::setPassword(const QString password)
{    
	QMutexLocker M(&_mutex);
	if (_password == QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1))
        return;

    _password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
}

void UserDataBase::setSurname(const QString surname)
{
	QMutexLocker M(&_mutex);
	if (_surname == surname)
        return;

    _surname = surname;
}

void UserDataBase::setLevel(quint8 level)
{
	QMutexLocker M(&_mutex);
	if (_level == level)
        return;

    _level = level;
}

void UserDataBase::enable(bool enabled)
{
	QMutexLocker M(&_mutex);
	if (_enabled == enabled)
        return;

    _enabled = enabled;
}

void UserDataBase::setNode(TreeData* node)
{
	QMutexLocker M(&_mutex);
	if ( ! node || _node == node)
        return;

	disconnect(this, SLOT(nodeRemoved()));
	_node = node;
	connect(_node, SIGNAL(removed()), this, SLOT(nodeRemoved()));
}

void UserDataBase::setLanguage(const QString language)
{
	QMutexLocker M(&_mutex);
	if (_language == language)
        return;

    _language = language;
}

void UserDataBase::setCountry(const QString country)
{
	QMutexLocker M(&_mutex);
	if (_country == country)
        return;

    _country = country;
}

void UserDataBase::setPhone(const QString phone)
{
	QMutexLocker M(&_mutex);
	if (_phone == phone)
        return;

    _phone = phone;
}

void UserDataBase::setAddress(const QString address)
{
	QMutexLocker M(&_mutex);
	if (_address == address)
        return;

    _address = address;
}

void UserDataBase::setBirthDate(const QDate birthDate)
{
	QMutexLocker M(&_mutex);
	if (_birthDate == birthDate)
        return;

    _birthDate = birthDate;
}

void UserDataBase::setPicture(const QVariant picture)
{
	QMutexLocker M(&_mutex);
	if (_picture == picture)
        return;

    _picture = picture;
}

#ifdef HORUS_CLIENT
#include <QIcon>
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
quint8 UserDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT login,level,password,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

    _login      = query.value(0).toString();
    _level      = (UserLevel)(query.value(1).toUInt());
	_password   = QByteArray::fromHex(query.value(2).toByteArray());
	_lastLogin  = query.value(3).toDateTime();
	_surname    = query.value(4).toString();
	_name       = query.value(5).toString();
	_birthDate  = query.value(6).toDate();
	_picture    = query.value(7).toByteArray();
	_address    = query.value(8).toString();
	_phone      = query.value(9).toString();
	_country    = query.value(10).toString();
	_language   = query.value(11).toString();
	disconnect(this, SLOT(nodeRemoved()));
	_node		= _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(12).toUInt() );
	connect(_node, SIGNAL(removed()), this, SLOT(nodeRemoved()));
	_enabled    = query.value(13).toBool();
	_lastChange	= query.value(14).toDateTime();

	return NONE;
}

quint8 UserDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO users (login,level,password,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
    query.addBindValue(_login);
    query.addBindValue(_level);
	query.addBindValue(_password.toHex());
	query.addBindValue(_lastLogin);
    query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue(_picture);
    query.addBindValue(_address);
    query.addBindValue(_phone);
    query.addBindValue(_country);
    query.addBindValue(_language);
	query.addBindValue(_node->id());
    query.addBindValue(_enabled);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	((UserDataBasePlugin*)_plugin)->users.remove(_id);
	_id = query.lastInsertId().toUInt();
	((UserDataBasePlugin*)_plugin)->users.insert(_id, this);

	return NONE;
}

quint8 UserDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE users SET login=?,level=?,password=?,last_login=?,surname=?,name=?,birth_date=?,picture=?,address=?,phone=?,country=?,language=?,id_tree=?,enabled=?,mtime=? WHERE id=?;");
    query.addBindValue(_login);
    query.addBindValue(_level);
	query.addBindValue(_password.toHex());
	query.addBindValue(_lastLogin);
    query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue(_picture);
    query.addBindValue(_address);
    query.addBindValue(_phone);
    query.addBindValue(_country);
    query.addBindValue(_language);
	query.addBindValue(_node->id());
    query.addBindValue(_enabled);    
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
    query.addBindValue(_id);

    if ( ! query.exec())
    {
		qDebug() << query.lastError();
		return DATABASE_ERROR;
    }
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}

quint8 UserDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM users WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}

QByteArray UserDataBase::newSession(const QDateTime& end)
{
	QMutexLocker M(&_mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	QByteArray session;
    qsrand(QTime::currentTime().msec() + _id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

    query.prepare("UPDATE users SET session_key=?, session_end=? WHERE id=?;");
    query.addBindValue(session.toHex());
    query.addBindValue(end);
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return QByteArray();
	}
	if ( ! query.numRowsAffected())
		return QByteArray();

    return session;
}

void UserDataBase::destroySession()
{
	QMutexLocker M(&_mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE users SET session_key='', session_end='' WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}

void UserDataBase::updateLastLogin()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE users SET last_login=? WHERE id=?;");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}
#endif
