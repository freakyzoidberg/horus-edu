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
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QSemaphore>
#include <QHash>

#include "../Common/UserData.h"
#include "../Common/CommSocket.h"

//! a ClientSocket created for each connexion
/*!
 * This Object destroy himself when the connexion is closed
 */
class ClientSocket : public CommSocket
{
  Q_OBJECT

public:
    //! Construct called by "Server"
    ClientSocket(int _socket, QObject* parent = 0);
    ~ClientSocket();

    enum        Status {INIT, CONNECTED};
    Status      status;

    //! Contain the list of connected users with the coresponding socket
    static QHash<UserData*,ClientSocket*> connectedUsers; //TODO: protect against simultaneous access with a mutex

    //! contain the user connected with this socket
    UserData* user;

    //! wait for other threads
    /*!
     * thread safe
     * called by the logout thread
     */
    void waitOtherThreads();

    //! allow multithreading for the user
    /*!
     * thread safe
     * called by the login thread
     * before the init and login phase, multithreading is not allowed for a single connexion
     */
    void allowOtherThreads();

private slots:
    //! called when a packet may be present on the socket
    void packetAvailable(const QByteArray&);
    //! if the connexion is closed, look if some thread are still running
    void tryToDelete();
    //! called when an ThreadPacket is destroyed
    void threadFinished();

    void ready();

private:
    //! read the next packet if there's available thread and packet
    void tryToReadPacket();
    //! lock the number of threads to MAX_USER_THREADS
    QSemaphore  threads;
    //! number of running threads
    quint32     nbThreads;
    //! queue of packets to execute
    QList<QByteArray> recvQueue;

//! to remove, just for debug message in cronstruct
public:
    quint32     id;
private:
    static quint32 nbCon;
};

#endif // CLIENTSOCKET_H
