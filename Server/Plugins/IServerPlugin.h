#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "../../Common/ModulePacket.h"

class IServer;

class IServerPlugin : public QObject
{
  Q_OBJECT
  public:
    //! the instance of the IServer given to the module
    IServer* server;
    //! return the name of the module
    virtual const QByteArray name() const = 0;
    //! return the version of the module
    virtual quint8           version() const = 0;

    //! method called by the server core when a packet for this module is received
    virtual void recvPacket(quint32 userId, const ModulePacket&) const = 0;
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
