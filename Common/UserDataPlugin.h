#ifndef USERDATAPLUGIN_H
#define USERDATAPLUGIN_H

#include "Defines.h"

#include <QHash>
#include "DataPlugin.h"

class UserData;
class UserDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin Plugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin Plugin)
#endif

public:
    inline const QString pluginName() const { return "UserDataPlugin"; }
    inline const QString getDataType() const { return "UserData"; }
    virtual UserData*    getUser(quint32 userId) = 0;

#ifdef HORUS_SERVER
    virtual void         userDisconnected(UserData* user) = 0;
    virtual UserData*    authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password) = 0;
    virtual UserData*    authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion) = 0;
#endif
};


#ifdef HORUS_SERVER
typedef UserDataPlugin ServerUserDataPlugin;
//HORUS_DECLARE_INTERFACE(UserDataPlugin);
Q_DECLARE_INTERFACE(ServerUserDataPlugin, "net.horus.ServerUserDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef UserDataPlugin ClientUserDataPlugin;
//HORUS_DECLARE_INTERFACE(UserDataPlugin);
Q_DECLARE_INTERFACE(ClientUserDataPlugin, "net.horus.ClientUserDataPlugin/1.0");
#endif

#endif // USERDATAPLUGIN_H
