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
#include <QByteArray>

#include "CommPlugin.h"
#include "PluginPacket.h"

CommPlugin::CommPlugin(const PluginPacket& mp)
    : CommPacket(CommPacket::PLUGIN)
{
    packet = mp;
}

CommPlugin::CommPlugin(const QByteArray& a)
    : CommPacket(CommPacket::PLUGIN)
{
    read(a);
}

const QByteArray CommPlugin::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommPlugin::read(const QByteArray& a)
{
    QDataStream stream(a);
    stream.device()->seek(lenParent());
    stream >> packet;
}

void CommPlugin::write(QByteArray& a) const
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek( lenParent() );
    stream << packet;
}

QDebug operator<<(QDebug d, const CommPlugin& cp)
{ return d
    << (CommPacket&)cp
    << cp.packet.sourcePlugin
    << cp.packet.targetPlugin
    << cp.packet.request
    //<< cm.packet // SEGFAULT ????
; }
