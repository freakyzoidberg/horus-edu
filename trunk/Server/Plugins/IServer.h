#ifndef ISERVER_H
#define ISERVER_H

#include "../../Common/PluginPacket.h"

class IServerPlugin;

//! Interface given to each plugin to communicate with the server
class IServer
{
public:
    //! methode to send a packet from a server plugin to a client plugin
    virtual void           sendPacket(const quint32 userId, const PluginPacket& packet) const = 0;
    //! return a Sql instance;
    virtual QByteArray* GetSql() const = 0;
    //! return another plugin loaded, return 0 if not found
    virtual IServerPlugin* getPlugin(const char* name) const = 0;
};

#endif // ISERVER_H
