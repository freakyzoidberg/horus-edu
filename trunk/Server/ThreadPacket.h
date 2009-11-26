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
#ifndef THREADPACKET_H
#define THREADPACKET_H

#include <QRunnable>
#include <QObject>

#include "ClientSocket.h"
#include "../Common/CommError.h"

//! This Object is a thread for each packet readed on the client socket
class ThreadPacket : public QObject, public QRunnable
{
  Q_OBJECT

  typedef void(ThreadPacket::*packetDirection)();

public:
    ThreadPacket(ClientSocket* cs, const QByteArray& pac);

    //! read the first CommPacket and go to the associed method
    /*!
     * read the socket until finding a good CommPacket
     * it's also the entry point of the thread
     */
    void run();

private:
    void PacketUndefined();
    void PacketError();
    void PacketInit();
    void PacketAlive();
    void PacketLogin();
    void PacketData();
    void PacketPlugin();

    //! send an error to the client
    void sendError(CommError::Error err, const char* str="") const;

    //! a pointer to the parent ClientSocket
    ClientSocket* socket;
    //! the received packet
    /*! every methods of ThreadPacket read and truncate this value
     */
    QByteArray    packet;

    //! corespondance table between CommPacket::type and the methods
    static packetDirection packetDirections[];

signals:
    //! signal emmited when a packet need to be send to the client
    void sendPacket(const QByteArray) const;
    //! signal emmited when a packet need to be send to a client on an other socket (need to be connected first)
    void sendPacketToAnotherSocket(const QByteArray) const;
};

#endif // THREADPACKET_H
