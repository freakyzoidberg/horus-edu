#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "../../Common/PluginPacket.h"

class IServer;

class IServerPlugin : public QObject
{
  Q_OBJECT
  public:
    //! the instance of the IServer given to the plugin
    IServer* server;
    //! return the name of the plugin
    virtual const QByteArray name() const = 0;
    //! return the version of the plugin
    virtual quint8           version() const = 0;

    //! method called by the server core when a packet for this plugin is received
    virtual void recvPacket(quint32 userId, const PluginPacket&) const = 0;
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
