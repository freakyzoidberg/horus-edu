#ifndef TESTCOMM_H
#define TESTCOMM_H

#include <QDebug>

//#include "../IServer.h"
#include "../IServerPlugin.h"

class TestComm : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    TestComm();
    ~TestComm();

public:
    inline const QByteArray  name() const { return "TestComm"; }
    inline const QByteArray  version() const { return "42"; }

    void recvPacket(quint32 userId, const ModulePacket&) const;
};


#endif // TESTCOMM_H
