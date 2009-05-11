#include "UserSettings.h"

#include <QByteArray>
#include <QDataStream>

UserSettings::UserSettings(quint32 _userId, const QByteArray& _module, CommSettings::Scope _scope)
{
    userId = _userId;
    module = _module;
    scope = _scope;
    exist = false;
    readDatabase();
}

void UserSettings::readDatabase()
{
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    query.prepare("SELECT value FROM settings WHERE user=? AND module=? AND scope=?;");
    query.addBindValue(userId);
    query.addBindValue(module);
    query.addBindValue(scope);

    qDebug() << "QUERY:" << query.executedQuery();

    if ( ! query.exec() || ! query.next())
    {
        qDebug() << query.lastError();
        return;
    }

    settings = query.value(0).toByteArray();
    exist = true;
}

void UserSettings::set(const QByteArray& _settings)
{
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    if ( ! exist)
        query.prepare("INSERT INTO settings (value,user,module,scope) VALUES (?,?,?,?);");
    else if (settings != _settings)
        query.prepare("UPDATE settings SET value=? WHERE user=? AND module=? AND scope=?;");
    else
        return;//Up to date

    query.addBindValue(_settings, QSql::Binary);
    query.addBindValue(userId);
    query.addBindValue(module);
    query.addBindValue(scope);

    qDebug() << "QUERY:" << query.executedQuery();
    if ( ! query.exec())
    {
        qDebug() << query.lastError();
        return;
    }

    settings = _settings;
}

const QByteArray& UserSettings::get()
{
    return settings;
}
