#ifndef ISERVER_H
#define ISERVER_H

#include <QObject>
#include <QString>

#include "../../Common/ModulePacket.h"
#include "IServerPlugin.h"

class IServerPlugin;

//! Interface given to each module to communicate with the server
class IServer
{
public:
    virtual void           sendPacket(const quint32 userId, const ModulePacket& packet) const = 0;

    virtual IServerPlugin* getModule(const char* name) const = 0;

//ADD EVERYTHING A MODULE CAN NEED
};

Q_DECLARE_INTERFACE(IServer, "net.horus.Server.Interface/1.0");

#endif // ISERVER_H
