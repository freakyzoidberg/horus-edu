#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "../../Common/PluginPacket.h"
#include "IServer.h"
//class IServer;

//! Interface of the Server Plugins
class IServerPlugin : public QObject
{
  public:
    //! the instance of the IServer given to the plugin
    IServer* server;
    //! return the name of the plugin
    virtual const QByteArray name() const = 0;
    //! return the version of the plugin
    virtual const QByteArray version() const = 0;

    //! called when the server realy start
    virtual inline bool start() { return true; }
    //! called before the server realy stop
    virtual inline bool stop() { return true; }

    //! method called by the server when a packet for this plugin is received
    virtual inline void recvPacket(quint32 userId, const PluginPacket& packet) {
        PluginPacket response(packet.sourcePlugin, packet.request);
        response.error = 1;
        response.errorMessage = "This plugin don't support packet reception.";
        server->sendPacket(userId, response);
    }
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
