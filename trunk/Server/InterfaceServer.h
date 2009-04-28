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

    void             sendPacket(const quint32 userId, const ModulePacket& packet) const;

    IServerPlugin*   getPlugin(const char* name) const;

private:
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
