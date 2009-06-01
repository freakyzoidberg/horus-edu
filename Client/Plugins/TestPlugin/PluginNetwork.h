#ifndef PLUGINNETWORK_H
#define PLUGINNETWORK_H

#include <QEvent>
#include <QtPlugin>
#include <QObject>
#include "../../INetworkPlugin.h"


//!  Access to the network
/*!
    Plugins can need an access to the network. For security, Horus don't
    allow plugins to have a direct access to the socket.

    To send packet through the network plugins must implement the interface
    IPluginNetwork from the Horus API. This class allow the plugin to give
    data to the client, which will send them on the network

    It inheritates QObject and the interface (horus API) IPluginNetwork
*/

class   PluginNetwork : public QObject, public IPluginNetwork
{
 //! The Q_OBJECT and Q_INTERFACES macros
 /*! This two macros must be called to compile the plugin properly.
    The second one take the name of the interface IPluginNetwork
    in parameters.
 */

 Q_OBJECT
 Q_INTERFACES(IPluginNetwork)

public:
        //! The constructor
        /*!
            empty
        */
        PluginNetwork();

        PluginPacket    *recvPacket() const;

        //! Handle the events NetworkEvent
        /*!
          If the plugin received a network event, this method must handle it

            \param event the event received
            \return true if the event was successfully handled, false eitherway
        */
       // bool    eventHandler(QEvent *event);

        //! Retrieved a packet
        /*!
          This method doesn't read directly on the socket. The client reads the socket
          and store the packet until the plugin can retrieve it
        */
        //void    retrievedPacket();

        //! Send a packet
        /*!
          This method doesn't write directly on the socket. It passes a packet
          to the client wich will send the packet on the network.
        */
        //void    buildPacket();
};

#endif // PLUGINNETWORK_H
