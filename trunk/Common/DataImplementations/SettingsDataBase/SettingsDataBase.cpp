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
    else if (owner == 0)
        _owner = plugin->pluginManager->currentUser();
    else
        _owner = owner;

    qDebug() << "user nobody:" << _owner;

#ifdef HORUS_SERVER
    inDatabase = false;
#endif
}

void SettingsDataBase::keyToStream(QDataStream& s)
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
    Data::dataToStream(s);
}

QDebug SettingsDataBase::operator<<(QDebug debug) const
{
    return debug << _part
                 << _scope
                 << _owner->login()
                 << _values;
}

void SettingsDataBase::setValue(const QString& key, const QVariant& val)
{
    if (_values[key] == val)
        return;

    _values[key] = val;
}

#ifdef HORUS_SERVER
quint8 SettingsDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT value,mtime FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _values = QVariantHash();
		return NONE;
    }
    inDatabase = true;
    _values = query.value(0).toHash();
    _lastChange = query.value(1).toDateTime();

	return NONE;
}

quint8 SettingsDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO settings (user,plugin,scope,value,mtime) VALUES (?,?,?,?,?);");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    query.addBindValue(_values);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    if ( ! query.exec() || ! query.next())
		return DATABASE_ERROR;

	return NONE;
}

quint8 SettingsDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	if ( ! inDatabase)
		return serverCreate();

    query.prepare("UPDATE settings SET value=?,mtime=? WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_values);
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    if ( ! query.exec() || ! query.next())
		return NOT_FOUND;

	return NONE;
}

quint8 SettingsDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner->id());
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
		return NOT_FOUND;

	return NONE;
}
#endif
