#include "SettingsDataBase.h"
#include "SettingsDataBasePlugin.h"

#include "../../PluginManager.h"
#include "../../UserData.h"

SettingsDataBase::SettingsDataBase(SettingsDataBasePlugin* plugin, QString part, quint8 scope, UserData* owner)
        : SettingsData((SettingsDataPlugin*)plugin)
{
    _part = part;
    _scope = scope;
    if IS_SYSTEM_SCOPE(scope)
		_owner = plugin->pluginManager->findPlugin<UserDataPlugin*>()->nobody();
	else
	{
		if (owner == 0)
			_owner = plugin->pluginManager->currentUser();
		else
			_owner = owner;
		connect(_owner, SIGNAL(removed()), this, SLOT(remove()));
	}
#ifdef HORUS_SERVER
    inDatabase = false;
#endif
}

void SettingsDataBase::keyToStream(QDataStream& s) const
{
    s << _part
      << _scope
      << _owner->id();
}

void SettingsDataBase::dataToStream(QDataStream& s) const
{
    s << _values;
    Data::dataToStream(s);
}

void SettingsDataBase::dataFromStream(QDataStream& s)
{
    s >> _values;
	Data::dataFromStream(s);
}

bool SettingsDataBase::canChange(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR)
		return true;
	if (IS_USER_SCOPE(_scope) && _owner == user)
		return true;
	return false;
}

bool SettingsDataBase::canAccess(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR)
		return true;
	if (IS_SYSTEM_SCOPE(_scope))
		return true;
	if (IS_USER_SCOPE(_scope) && _owner == user)
		return true;
	return false;
}

QDebug SettingsDataBase::operator<<(QDebug debug) const
{
    return debug << _part
                 << _scope
                 << _owner->login()
                 << _values;
}

const QList<Data*> SettingsDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_owner);
	return list;
}

void SettingsDataBase::setValue(const QString& key, const QVariant& val)
{
	QMutexLocker M(&mutex);
	_values[key] = val;
}

#ifdef HORUS_SERVER
quint8 SettingsDataBase::serverRead()
{
	_values = QVariantHash();
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`value`,`mtime`FROM`setting`WHERE`user`=? AND`part`=? AND`scope`=?;");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NONE;

    inDatabase = true;
    _values = query.value(0).toHash();
    _lastChange = query.value(1).toDateTime();

	return NONE;
}

quint8 SettingsDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`setting`(`user`,`part`,`scope`,`value`,`mtime`)VALUES(?,?,?,?,?);");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    query.addBindValue(_values);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	return NONE;
}

quint8 SettingsDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	if ( ! inDatabase)
		return serverCreate();

	query.prepare("UPDATE`setting`SET`value`=?,`mtime`=? WHERE`user`=? AND`part`=? AND`scope`=?;");
    query.addBindValue(_values);
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 SettingsDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`setting`WHERE`user`=? AND`part`=? AND`scope`=?;");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}
#endif
