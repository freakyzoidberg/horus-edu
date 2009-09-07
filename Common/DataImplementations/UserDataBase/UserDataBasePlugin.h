#ifndef USERDATABASEPLUGIN_H
#define USERDATABASEPLUGIN_H

#include <QHash>
#include "../../UserDataPlugin.h"

class Data;
class UserData;
class UserDataBase;
class UserDataBasePlugin : public UserDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerUserDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientUserDataPlugin)
#endif

public:
    inline const QString pluginVersion() const { return "0.1"; }
    UserData*            getUser(quint32 userId);

#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    void                 loadDataBase(QSqlQuery&);
    void                 userDisconnected(UserData* user);
    UserData*            authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    UserData*            authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
    void                 sendUpdates(QSqlQuery&, UserData* user, QDateTime date);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QHash<quint32,UserData*> users;
};

#endif // USERDATABASEPLUGIN_H
