#ifndef IPLUGINNETWORK_H
#define IPLUGINNETWORK_H

#include "INetwork.h"

//! Interface optionnal for using the network
/*!
 *  Each plugin implementing this interface will be able to use the network: send and receive packets.
 */
class INetworkPlugin
{
    public:
    //! Pointer to an implementation of the interface INetwork
    /*!
     *  This pointer is set by the Client while loading the plugin.
     *  It let plugin access network ressources
     */
    INetwork    *network;
    //! method called by the server core when a packet for this plugin is received
    virtual void recvPacket(const PluginPacket&) = 0;
};

Q_DECLARE_INTERFACE(INetworkPlugin, "net.horus.Client.NetworkInterface/1.0");

#endif // IPLUGINNETWORK_H
