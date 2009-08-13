#include "SettingsDataBase.h"
#include "SettingsDataBasePlugin.h"

SettingsDataBase::SettingsDataBase(SettingsDataBasePlugin* plugin, QString part, quint8 scope, quint32 ownerId)
        : SettingsData((SettingsDataPlugin*)plugin)
{
    _part = part;
    _scope = scope;
    _owner = ownerId;
#ifdef HORUS_SERVER
    inDatabase = false;
#endif
}

void SettingsDataBase::keyToStream(QDataStream& s)
{
    s << _part
      << _scope
      << _owner;
}

void SettingsDataBase::dataToStream(QDataStream& s)
{
    s << _values;
}

void SettingsDataBase::dataFromStream(QDataStream& s)
{
    s >> _values;
}

QDebug SettingsDataBase::operator<<(QDebug debug) const
{
    return debug << _part
                 << _scope
                 << _owner
                 << _values;
}

#ifdef HORUS_SERVER
void SettingsDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT value FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
//        _error = NOT_FOUND;
        _values = QVariantHash();
        return;
    }
    inDatabase = true;
    _values = query.value(0).toHash();
}

void SettingsDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO settings (user,plugin,scope,value) VALUES (?,?,?,?);");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    query.addBindValue(_values);
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

    query.prepare("UPDATE settings SET value=? WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_values);
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

void SettingsDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif
