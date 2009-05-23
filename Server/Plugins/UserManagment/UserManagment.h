#ifndef TESTCOMM_H
#define TESTCOMM_H

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class UserManagment : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

  typedef void (UserManagment::*requestFunction)(const QVariantHash& request,QVariantHash& response);

public:
    inline const QByteArray  name()    const { return "UserManagment"; }
    inline quint8            version() const { return 0; }

    void recvPacket(quint32 userId, const PluginPacket&);

private:
    static QHash<QByteArray,requestFunction> requestFunctions;

    void  unknownRequest(const QVariantHash& request,QVariantHash& response);
    void  changePassword(const QVariantHash& request,QVariantHash& response);
    void      createUser(const QVariantHash& request,QVariantHash& response);
};

#endif // TESTCOMM_H
