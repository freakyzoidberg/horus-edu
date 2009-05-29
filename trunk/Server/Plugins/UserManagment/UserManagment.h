#ifndef TESTCOMM_H
#define TESTCOMM_H

#include <QtSql>

#include "../IServer.h"
#include "../IServerPlugin.h"
#include "../../Sql.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class UserManagment : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

  typedef void (UserManagment::*requestFunction)(quint32 userId, const QVariantHash& request,QVariantHash& response);

public:
    UserManagment();

    inline const QByteArray  name()    const { return "UserManagment"; }
    inline quint8            version() const { return 0; }

    void recvPacket(quint32 userId, const PluginPacket&);

private:
    QHash<QByteArray,requestFunction> requestFunctions;

    void unknownRequest     (quint32 userId, const QVariantHash& request,QVariantHash& response);
    void changeMyPassword   (quint32 userId, const QVariantHash& request,QVariantHash& response);
    void changeUserPassword (quint32 userId, const QVariantHash& request,QVariantHash& response);
    void createUser         (quint32 userId, const QVariantHash& request,QVariantHash& response);
};

#endif // TESTCOMM_H
