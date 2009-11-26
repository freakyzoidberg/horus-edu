/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
