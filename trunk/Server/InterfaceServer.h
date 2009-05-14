#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include <QString>

#include "Plugins/IServer.h"
#include "../Common/CommPlugin.h"

//! Interface given to each plugin to communicate with the server
class InterfaceServer : public IServer
{
public:
    InterfaceServer(IServerPlugin*);

    //! methode to send a packet from a server plugin to a client plugin
    void             sendPacket(const quint32 userId, const PluginPacket& packet) const;

    //! return another plugin loaded, return 0 if not found
    IServerPlugin*   getPlugin(const char* name) const;

private:
    //! instance of the associated plugin
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
