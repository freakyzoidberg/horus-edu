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
#include "CommSocket.h"
#include "CommPacket.h"
#include <QtEndian>
#include <QSsl>

CommSocket::CommSocket(QObject* parent) : QSslSocket(parent)
{
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
	connect(this, SIGNAL(sslErrors(QList<QSslError>)),         this, SLOT(sslErrorsSlot(QList<QSslError>)));

    //TODO later: For test
    setPeerVerifyMode(QSslSocket::VerifyNone);

    sizePacket = 0;
    connect(this, SIGNAL(readyRead()), this, SLOT(bytesReceived()));
}

void CommSocket::errorSlot(QAbstractSocket::SocketError e)
{
	qDebug() << e;
}

void CommSocket::sslErrorsSlot(QList<QSslError> e)
{
	qDebug() << e;
}

void CommSocket::bytesReceived()
{
    if ( ! sizePacket)
    {
        if ((quint32)bytesAvailable() < sizeof(sizePacket))
            return;
        read((char*)&sizePacket, sizeof(sizePacket));
        sizePacket = qFromLittleEndian(sizePacket);
    }

    if (bytesAvailable() < sizePacket)
        return;

    QByteArray pac(sizePacket, 0);
    read(pac.data(), sizePacket);

    sizePacket = 0;

    CommPacket::debugPacket((qDebug() << "[ in]"), pac);
    emit packetReceived(pac);
    emit readyRead();
}

void CommSocket::sendPacket(const QByteArray pac)
{
    quint32 size = qToLittleEndian(pac.length());
    write((char*)&size, sizeof(size));
    write(pac.data(), size);
    flush();

    CommPacket::debugPacket((qDebug() << "[out]"), pac);
}
