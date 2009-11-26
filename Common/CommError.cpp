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
#include <QObject>

#include "CommError.h"

CommError::CommError(Error _type, const char* _errorMessage) : CommPacket(CommPacket::PACKET_ERROR)
{
    static const QString  typeNames[] =
    {
		QObject::tr("Unknow Error"),
        QObject::tr("Connexion not initialized"),
        QObject::tr("Connexion already initialized"),
        QObject::tr("Not authenticated"),
        QObject::tr("Unknown protocol version"),
        QObject::tr("Protocol Error"),
        QObject::tr("Internal Error")
    };

    errorType = _type;
    if ( ! _errorMessage || ! _errorMessage[0])
        errorMessage = qPrintable(typeNames[ errorType ]);
    else
        errorMessage = _errorMessage;
}

CommError::CommError(const QByteArray& a) : CommPacket(CommPacket::PACKET_ERROR)
{
    errorType = UNDEFINED;
    read(a);
}

const QByteArray CommError::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommError::read(const QByteArray& a)
{
    int len = lenParent();
    if ((char)a[ len ] < (char)__LAST__)
        errorType = (Error)(char)a[ len ];
    errorMessage = a.mid(len + 1);
}

void CommError::write(QByteArray& a) const
{
    a.append(errorType);
    a.append(errorMessage);
}

QDebug operator<<(QDebug d, const CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
