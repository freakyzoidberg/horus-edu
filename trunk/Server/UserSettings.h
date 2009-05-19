#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QByteArray>

#include "../Common/CommSettings.h"

//! Interface to get/set the CommSettings values into the database. there is not security checks
class UserSettings
{
public:
    UserSettings(quint32 userId, const QByteArray& plugin, CommSettings::Scope scope);

    //! set a scope value
    void              set(const QByteArray& settings);
    //! get a scope value
    const QByteArray& get();

private:
    //! called by the constructor to get the target value when it's instancied
    void              readDatabase();

    quint32           userId;
    QByteArray        plugin;
    CommSettings::Scope scope;
    bool              exist;
    QByteArray        settings;
};

#endif // USERSETTINGS_H
