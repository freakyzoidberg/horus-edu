#ifndef NETWORKPLUGINSERVER_H
#define NETWORKPLUGINSERVER_H

#include "../Common/Plugin.h"
#include "../Common/PluginPacket.h"
#include "../Common/UserData.h"

/*!
 * run in the network thread
 */
class NetworkPlugin : public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

public slots:
    //! method called by the server core when a packet for this plugin is received
    /*!
     *  \param packet the received packet
     */
    virtual void receivePacket(UserData* user, const PluginPacket) = 0;

signals:
    //! a signal emmited to send packets to a plugin of the other side
    /*!
     *  \param packet the packet to send
     */
    void sendPacket(UserData* user, const PluginPacket packet);
};

typedef NetworkPlugin NetworkPluginServer;
Q_DECLARE_INTERFACE(NetworkPluginServer, "net.horus.NetworkPluginServer/1.0");

#endif // NETWORKPLUGINSERVER_H
