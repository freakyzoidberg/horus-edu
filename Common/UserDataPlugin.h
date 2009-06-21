#ifndef USERDATAPLUGIN_H
#define USERDATAPLUGIN_H

#include <QHash>
#include "DataPlugin.h"

class UserData;
class UserDataPlugin : public DataPlugin
{
  Q_OBJECT
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

#endif // USERDATAPLUGIN_H
