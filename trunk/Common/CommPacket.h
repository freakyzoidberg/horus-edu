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
#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QByteArray>
#include <QDebug>

#include "Defines.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
//! Parent Communication packet. Just define the type of the transmited packet
class CommPacket
{
public:
    //! type of the packet
    /*!
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is used to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
	enum                Type { UNDEFINED, PACKET_ERROR, INIT, ALIVE, LOGIN, DATA, PLUGIN, __LAST__ };

    //! constuctor to send a new packet
    CommPacket(Type _type);
    //! constructor when receiving a packet (just call a read())
    CommPacket(const QByteArray&);
    //! create the concated packet
    const QByteArray    getPacket() const;

    static void debugPacket(QDebug, const QByteArray&);

    //! type of the packet
    Type                packetType;

protected:
    void                read(const QByteArray&);
    void                write(QByteArray&) const;
    inline int          lenParent() const { return 1; }
};

QDebug operator<<(QDebug, const CommPacket&);

#endif // COMMPACKET_H
