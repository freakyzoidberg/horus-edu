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
