#ifndef USERDATASTDPLUGIN_H
#define USERDATASTDPLUGIN_H

#include <QHash>
#include "../../UserDataPlugin.h"
#include "../../UserData.h"

class UserDataStdPlugin : public UserDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerUserDataPlugin ServerDataPlugin Plugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientUserDataPlugin ClientDataPlugin Plugin)
#endif

public:
    inline const QString pluginVersion() const { return "0.1"; }
    UserData*            getUser(quint32 userId);

#ifdef HORUS_CLIENT
    void dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    bool      verifyDataBase(QSqlQuery&);
    void      userDisconnected(UserData* user);
    UserData* authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    UserData* authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
#endif

private slots:
    void dataDeleted();

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*         getDataWithKey(QDataStream& s);

private:
    QHash<quint32,UserData*> users;
};

#endif // USERDATASTDPLUGIN_H
