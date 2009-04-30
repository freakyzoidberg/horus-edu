#ifndef ICLIENT_H
#define ICLIENT_H

#include "../Common/ModulePacket.h"
#include "IClientPlugin.h"

//! Interface given to each client plugin to communicate with the client
class Iclient
{
public:
    virtual void            sendPacket(const ModulePacket& packet) const = 0;
    virtual void            recvPacket(const ModulePacket& packet) const = 0;
    virtual IClientPlugin*  getPlugin(const char* name) const = 0;
};

Q_DECLARE_INTERFACE(IClientPlugin, "net.horus.Client.PluginClientInterface/1.0");

#endif // ICLIENT_H
