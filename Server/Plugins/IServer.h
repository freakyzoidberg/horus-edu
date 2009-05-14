#ifndef ISERVER_H
#define ISERVER_H

#include "../../Common/ModulePacket.h"

class IServerPlugin;

//! Interface given to each module to communicate with the server
class IServer
{
public:
    //! methode to send a packet from a server module to a client module
    virtual void           sendPacket(const quint32 userId, const ModulePacket& packet) const = 0;

    //! return another plugin loaded, return 0 if not found
    virtual IServerPlugin* getPlugin(const char* name) const = 0;
};

#endif // ISERVER_H
