#ifndef TESTCOMM_H
#define TESTCOMM_H

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class UserManagment : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    inline const QByteArray  name()    const { return "UserManagment"; }
    inline quint8            version() const { return 0; }

    void recvPacket(quint32 userId, const PluginPacket&) const;
};


#endif // TESTCOMM_H
