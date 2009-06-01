#ifndef NETWORK_H
#define NETWORK_H

#include "IClientPlugin.h"

#include "../Common/PluginPacket.h"
#include "../Common/CommPlugin.h"

class   Network
{
public:
    Network();
    void            sendPacket(const PluginPacket& packet) const;

private:
    IClientPlugin   *plugin;

};

#endif // NETWORK_H
