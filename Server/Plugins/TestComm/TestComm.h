#ifndef TESTCOMM_H
#define TESTCOMM_H

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to test the communication between a Client Plugin and a Server Plugin
class TestComm : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    TestComm();
    ~TestComm();

public:
    inline const QByteArray  name()    const { return "TestComm"; }
    inline quint8            version() const { return 42; }

    void recvPacket(quint32 userId, const PluginPacket&);
};


#endif // TESTCOMM_H
