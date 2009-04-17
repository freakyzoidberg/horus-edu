#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include <QString>

#include "Plugins/IServer.h"
#include "Plugins/IServerPlugin.h"
#include "../Common/CommModule.h"
#include "User.h"

//! Interface given to each module to communicate with the server
class InterfaceServer : public IServer
{
public:
    void             sendPacket(const quint32 userId, const ModulePacket& packet) const;

    IServerPlugin*   getModule(const char* name) const;
};

#endif // INTERFACESERVER_H
