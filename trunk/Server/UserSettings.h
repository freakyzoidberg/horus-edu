#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QByteArray>

#include "Sql.h"

class UserSettings
{
public:
    UserSettings(quint32 userId, const QByteArray& module);

    void              set(const QByteArray& settings);
    const QByteArray& get();

private:
    void              readDatabase();

    quint32           userId;
    QByteArray        module;
    bool              exist;
    QByteArray        settings;
};

#endif // USERSETTINGS_H
