#ifndef INETWORKSENDER_H
#define INETWORKSENDER_H

#include "../Common/PluginPacket.h"

class   INetworkSender
{
 public:
    //! A function for providing to plugins the send of packets to the network
    /*!
     *  need to be in a network interface
     *  \param packet the packet to send
     */
    virtual void            sendPacket(const PluginPacket& packet) const = 0;

};

#endif // INETWORKSENDER_H
