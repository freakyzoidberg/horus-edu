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
#ifndef COMMSOCKET_H
#define COMMSOCKET_H

#include <QSslSocket>

//! Communication socket is a QSslSocket, shared onto Client and Server
class CommSocket : public QSslSocket
{
  Q_OBJECT
public:
    CommSocket(QObject* parent = 0);

private:
    //! size of the next packet to read
    /*! each packet is preceded by an uint32 containing the size of the packet
     *  while this size is not into the read buffer(QTcpSocket::byteAvailables()), nothing is read
     */
    quint32 sizePacket;

private slots:
    //! slot connected with QTcpSocket::readyRead(): when so data just arrived
    void bytesReceived();

    //! slot connected with QTcpSocket::error(): when an error occur on the socket
    void errorSlot(QAbstractSocket::SocketError e);
    //! slot connected with QSslSocket::sslErrors(): when an ssl error occur on the socket
    void sslErrorsSlot(QList<QSslError> e);

public slots:
    //! slot to send packet to a client
	void sendPacket(const QByteArray);

signals:
    //! signal emmitted when a packet is received
	void packetReceived(const QByteArray);
};

#endif // COMMSOCKET_H
