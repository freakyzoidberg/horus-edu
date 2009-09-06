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

class TreeData;
class UserData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
    inline int              id() const { return _id; }

    virtual const QString   login() const = 0;
    virtual const QDateTime lastLogin() const = 0;
    virtual bool            loggedIn() const = 0;

    virtual const QString   name() const = 0;
    virtual void            setName(const QString name) = 0;

    virtual const QString   surname() const = 0;
    virtual void            setSurname(const QString name) = 0;

    virtual quint8          level() const = 0;
    virtual void            setLevel(quint8 level) = 0;

    virtual bool            enabled() const = 0;
    virtual void            enable(bool enabled) = 0;

    virtual TreeData*       node() const = 0;
    virtual void            setNode(TreeData* node) = 0;

    virtual const QString   language() const = 0;
    virtual void            setLanguage(const QString language) = 0;

#ifdef HORUS_SERVER
    //! Create a random key to be able to identify a user without the password.
    virtual QByteArray newSession(QSqlQuery&, const QDateTime& end) = 0;
    //! Destroy the session generated to allow only password authentication.
    virtual void destroySession(QSqlQuery&) = 0;
#endif

protected:
    inline UserData(quint32 id, UserDataPlugin* plugin) : Data(plugin) { _id = id; }
    ~UserData() {}
    quint32 _id;
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
