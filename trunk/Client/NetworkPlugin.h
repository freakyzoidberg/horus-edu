#ifndef NETWORKPLUGINCLIENT_H
#define NETWORKPLUGINCLIENT_H

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
    virtual void receivePacket(const PluginPacket) = 0;

signals:
    //! a signal emmited to send packets to a plugin of the other side
    /*!
     *  \param packet the packet to send
     */
    void sendPacket(const PluginPacket packet);
};

typedef NetworkPlugin NetworkPluginClient;
Q_DECLARE_INTERFACE(NetworkPluginClient, "net.horus.NetworkPluginClient/1.0");

#endif // NETWORKPLUGINCLIENT_H
