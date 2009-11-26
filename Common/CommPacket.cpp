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
#include "CommPacket.h"

#include <QObject>

#include "CommData.h"
#include "CommError.h"
#include "CommInit.h"
#include "CommLogin.h"
#include "CommPlugin.h"

CommPacket::CommPacket(Type _type)
{
    packetType = _type;
}

CommPacket::CommPacket(const QByteArray& a)
{
    packetType = UNDEFINED;
    read(a);
}

const QByteArray CommPacket::getPacket() const
{
    QByteArray a;
    write(a);
    return a;
}

void CommPacket::read(const QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        packetType = (Type)(char)a[0];
}

void CommPacket::write(QByteArray& a) const
{
    a = QByteArray(1,(char)packetType);
}

QDebug operator<<(QDebug d, const CommPacket& cr)
{
    static const QString  typeNames[] =
    {
		QObject::tr("Unknow "),
        QObject::tr("Error  "),
        QObject::tr("Init   "),
        QObject::tr("Alive  "),
        QObject::tr("Login  "),
        QObject::tr("Data   "),
        QObject::tr("Plugin ")
    };
    return d << typeNames[ cr.packetType ] << '|';
}

void CommPacket::debugPacket(QDebug d, const QByteArray& src)
{
    CommPacket packet(src);
    if (packet.packetType == CommPacket::DATA)
        d << CommData(src);
	else if (packet.packetType == CommPacket::PACKET_ERROR)
        d << CommError(src);
    else if (packet.packetType == CommPacket::INIT)
        d << CommInit(src);
    else if (packet.packetType == CommPacket::LOGIN)
        d << CommLogin(src);
    else if (packet.packetType == CommPacket::PLUGIN)
        d << CommPlugin(src);
    else
        d << packet;
}
