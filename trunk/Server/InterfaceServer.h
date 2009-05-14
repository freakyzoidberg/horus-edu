#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include <QString>

#include "Plugins/IServer.h"
#include "../Common/CommModule.h"

//! Interface given to each module to communicate with the server
class InterfaceServer : public IServer
{
public:
    InterfaceServer(IServerPlugin*);

    //! methode to send a packet from a server module to a client module
    void             sendPacket(const quint32 userId, const ModulePacket& packet) const;

    //! return another plugin loaded, return 0 if not found
    IServerPlugin*   getPlugin(const char* name) const;

private:
    //! instance of the associated plugin
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
