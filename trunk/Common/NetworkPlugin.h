#ifndef NETWORKPLUGIN_H
#define NETWORKPLUGIN_H

#include "Plugin.h"

/*!
 * run in the network thread
 */
class NetworkPlugin : public Plugin
{
    //! method called by the server core when a packet for this plugin is received
    /*!
     *  \param packet the received packet
     */
    virtual void receivePacket(const PluginPacket&) = 0;

    //! A function provided to the plugins to send packets to a server plugin
    /*!
     *  \param packet the packet to send
     */
    virtual void sendPacket(const PluginPacket& packet) const = 0;
};

Q_DECLARE_INTERFACE(NetworkPlugin, "net.horus.NetworkPlugin/1.0");

#endif // NETWORKPLUGIN_H
