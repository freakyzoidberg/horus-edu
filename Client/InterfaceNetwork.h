#ifndef NETWORK_H
#define NETWORK_H

#include "INetwork.h"
#include "IClientPlugin.h"

class InterfaceNetwork : public INetwork
{
public:
    InterfaceNetwork();
    void sendPacket(const PluginPacket& packet) const;

private:
    IClientPlugin   *plugin;
};

#endif // NETWORK_H
