#ifndef ICLIENT_H
#define ICLIENT_H

#include "../Common/ModulePacket.h"
#include "IClientPlugin.h"

//! Interface given to each client plugin to communicate with the client
class IClient
{
public:
    virtual void            sendPacket(const ModulePacket& packet) const = 0;
    virtual void            recvPacket(const ModulePacket& packet) const = 0;
    virtual IClientPlugin   *getPlugin(const QByteArray name) const = 0;
};

Q_DECLARE_INTERFACE(IClient, "net.horus.Client.PluginClientInterface/1.0");

#endif // ICLIENT_H
