#ifndef USERDATA_H
#define USERDATA_H

#ifdef HORUS_SERVER
#include <QtSql>
#endif
#include <QByteArray>
#include <QDateTime>
#include "Defines.h"
#include "Data.h"
#include "UserDataPlugin.h"

class UserData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

protected:
    inline UserData(quint32 userId, UserDataPlugin* plugin) : Data(plugin) { id = userId; }
public:
    quint32     id;
    quint8      level;
    bool        enabled;
    QString     login;
    quint32     idTree;
    QString     name;
    QString     surname;
    QDateTime   lastLogin;
    QString     language;

#ifdef HORUS_SERVER
    //! Create a random key to be able to identify a user without the password.
    virtual QByteArray newSession(QSqlQuery&, const QDateTime& end) = 0;
    //! Destroy the session generated to allow only password authentication.
    virtual void destroySession(QSqlQuery&) = 0;
#endif

protected:
    ~UserData() {}
};

#ifdef HORUS_SERVER
typedef UserData ServerUserData;
Q_DECLARE_INTERFACE(ServerUserData, "net.horus.ServerUserData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef UserData ClientUserData;
Q_DECLARE_INTERFACE(ClientUserData, "net.horus.ClientUserData/1.0");
#endif

#endif // USERDATA_H
