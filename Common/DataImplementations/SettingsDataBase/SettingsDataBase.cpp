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
        _owner = plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser(0);
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
      << _owner->id;
}

void SettingsDataBase::dataToStream(QDataStream& s)
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
                 << _owner->login
                 << _values;
}

#ifdef HORUS_SERVER
void SettingsDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT value,mtime FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner->id);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _values = QVariantHash();
        return;
    }
    inDatabase = true;
    _values = query.value(0).toHash();
    _lastChange = query.value(1).toDateTime();
}

void SettingsDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO settings (user,plugin,scope,value,mtime) VALUES (?,?,?,?,?);");
    query.addBindValue(_owner->id);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    query.addBindValue(_values);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
}

void SettingsDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    if ( ! inDatabase)
        return createIntoDatabase(query);

    query.prepare("UPDATE settings SET value=?,mtime=? WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_values);
    query.addBindValue(_owner->id);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

void SettingsDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner->id);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif
