#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QByteArray>

#include "../Common/CommSettings.h"
#include "Sql.h"

class UserSettings
{
public:
    UserSettings(quint32 userId, const QByteArray& plugin, CommSettings::Scope scope);

    void              set(const QByteArray& settings);
    const QByteArray& get();

private:
    void              readDatabase();

    quint32           userId;
    QByteArray        plugin;
    CommSettings::Scope scope;
    bool              exist;
    QByteArray        settings;
};

#endif // USERSETTINGS_H
