#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QThreadPool>
#include <QSemaphore>

#include "User.h"
#include "../Common/CommSocket.h"

class User;

//! a ClientSocket created for each connexion
/*
 * This Object destroy himself when the connexion is closed
 */
class ClientSocket : public CommSocket
{
  Q_OBJECT

public:
    //! Construct called by "Server"
    ClientSocket(int _socket, QObject* parent = 0);
    ~ClientSocket();

    enum        tState {INIT, CONNECTED};
    tState      vState;

    //! the User object asociated with the socket
    User        user;

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

//    void sslErrorsSlot(QList<QSslError> e);
    void ready();
//    void socketError(QAbstractSocket::SocketError);

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
