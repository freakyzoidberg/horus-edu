#ifndef IPLUGINNETWORK_H
#define IPLUGINNETWORK_H

#include <QEvent>

//! Interface optionnal for using the network
/*!
 *  Each plugin implementing this interface will be able to use the network: send and receive packets.
 */
class INetworkPlugin
{
    public:
        //! Useless, must be deleted
        virtual bool    eventHandler(QEvent *) = 0;
        //! Must be moved in a interface of the client like IClient
        virtual void    retrievedPacket() = 0;
        //! Must be moved in a interface of the client like IClient
        virtual void    buildPacket() = 0;
};

Q_DECLARE_INTERFACE(INetworkPlugin, "net.horus.Client.NetworkInterface/1.0");

#endif // IPLUGINNETWORK_H
