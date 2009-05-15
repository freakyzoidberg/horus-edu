#ifndef ICLIENT_H
#define ICLIENT_H

#include "../Common/PluginPacket.h"
#include "IClientPlugin.h"

//! Interface given to each client plugin to communicate with the client
/*!
 *  This interface implements network relative functions which must be in a specific network interface
 */
class IClient
{
public:
    //! A function for providing to plugins the send of packets to the network
    /*!
     *  need to be in a network interface
     *  \param packet the packet to send
     */
    virtual void            sendPacket(const ModulePacket& packet) const = 0;
    //! A function for providing to plugins the read of packets to the network
    /*!
     *  need to be in a network interface
     *  \param packet a reference to the emplacement of the readed packet
     */
    virtual void            recvPacket(const ModulePacket& packet) const = 0;
    //! A function for accessing plugins from other plugins
    /*!
     *  This function return the instance of plugin from his name.
     *  A plugin can only be instancieted once, so each name is unique.
     *  It is destinated for plugins willing to contacts other plugins
     *  \param name the name of the desired plugin
     *  \return a pointer to the instance of the desired plugin or NULL if not found
     */
    virtual IClientPlugin   *getPlugin(const QByteArray name) const = 0;
};

Q_DECLARE_INTERFACE(IClient, "net.horus.Client.PluginClientInterface/1.0");

#endif // ICLIENT_H
