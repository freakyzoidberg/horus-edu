#ifndef USERDATASTDPLUGIN_H
#define USERDATASTDPLUGIN_H

#include <QHash>
#include "../../UserDataPlugin.h"
#include "../../UserData.h"

class UserDataStdPlugin : public UserDataPlugin
{
  Q_OBJECT
public:
    inline const QString pluginVersion() const { return "0.1"; }
    UserData*            getUser(quint32 userId);

#ifdef HORUS_SERVER
    bool      verifyDataBase(QSqlQuery&);
    void      userDisconnected(UserData* user);
    UserData* authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    UserData* authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*         getDataWithKey(QDataStream& s);

private:
    QHash<quint32,UserData*> users;
};

#endif // USERDATASTDPLUGIN_H
