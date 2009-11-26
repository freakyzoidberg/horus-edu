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
#ifndef PLUGINPACKET_H
#define PLUGINPACKET_H

#include <QDebug>
#include <QVariant>
#include <QDataStream>

class UserData;
//! communication class between server plugin and a client plugin
class PluginPacket
{
public:
    inline PluginPacket() { error=0; }
    inline PluginPacket(const QString& _target, const QString& _request, const QVariant& _data=QVariant()) { targetPlugin=_target; request=_request; data=_data; error=0;}

    //! version of the source plugin. For a plugin, it's not neccessary to fill this value
    QString packetVersion;
    //! source plugin. For a plugin, it's not neccessary to fill this value
    QString sourcePlugin;

    //! target plugin
    QString targetPlugin;
    //! request
    QString request;
    //! error code
    quint16    error;
    //! error message
    QString    errorMessage;
    //! data of the packet
    QVariant   data;

#ifdef HORUS_SERVER
    //! Just an information given by the server when receiving a packet. This field also need to be filled before sending a packet to this User.
    UserData* user;
#endif
};

QDebug& operator<<(QDebug& d, const PluginPacket& p);
QDataStream& operator<<(QDataStream& d, const PluginPacket& p);
QDataStream& operator>>(QDataStream& d, PluginPacket& p);

#endif // PLUGINPACKET_H
