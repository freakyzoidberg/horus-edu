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
#include "CommData.h"
#include "Data.h"
#include <QObject>

CommData::CommData(const QString& _type) : CommPacket(CommPacket::DATA)
{
    type = _type;
}

CommData::CommData(const QByteArray& a) : CommPacket(CommPacket::DATA)
{
    read(a);
}

const QByteArray CommData::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommData::read(const QByteArray& a)
{
    int len = lenParent();
    type = a.mid(len + 1,  a[ len ]);
    data = a.mid(len + 1 + a[ len ]);
}

void CommData::write(QByteArray& a) const
{
    a.append((char)type.length());
    a.append(type);
    a.append(data);
}

QDebug operator<<(QDebug d, const CommData& p)
{
	QDataStream stream(p.data);
	quint8 status;
	stream >> status;

	d << (CommPacket&)p << p.type << (Data::Status)status;
	if (status == Data::DATA_ERROR)
	{
		quint8 error;
		stream >> error;
		d << (Data::Error)error;
	}
	return d;
}
