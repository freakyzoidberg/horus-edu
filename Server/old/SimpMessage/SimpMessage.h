#ifndef SIMPMESSAGE_H
#define SIMPMESSAGE_H

#include <QDebug>

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to allow basic communication between users
class SimpMessage : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    SimpMessage();
    ~SimpMessage();

public:
    inline const QByteArray  name()    const { return "SimpMessage"; }
    inline quint8            version() const { return 42; }

    void recvPacket(quint32 userId, const PluginPacket&);
};


#endif // SimpMessage_H
