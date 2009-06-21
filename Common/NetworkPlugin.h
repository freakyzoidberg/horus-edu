#ifndef NETWORKPLUGIN_H
#define NETWORKPLUGIN_H

#include "Plugin.h"
#include "PluginPacket.h"
#include "UserData.h"

/*!
 * run in the network thread
 */
class NetworkPlugin : public Plugin
{
    Q_OBJECT

public slots:
    //! method called by the server core when a packet for this plugin is received
    /*!
     *  \param packet the received packet
     */
    virtual void receivePacket(UserData* user, const PluginPacket&) = 0;

signals:
    //! a signal emmited to send packets to a plugin of the other side
    /*!
     *  \param packet the packet to send
     */
    void sendPacket(UserData* user, const PluginPacket& packet);
};

Q_DECLARE_INTERFACE(NetworkPlugin, "net.horus.NetworkPlugin/1.0");

#endif // NETWORKPLUGIN_H
