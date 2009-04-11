#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>
#include <QMutex>
#include <QSemaphore>

//! ClientSocket created for each connexion
/*
 * This Object destroy himself when the connexion is closed
 */
class ClientSocket : public QObject
{
  Q_OBJECT

public:
    //! Construct called by "Server"
    /*!
      * \param _socket the integer file descriptor given by Server::incommingConexion()
      */
    ClientSocket(int _socket);
    ~ClientSocket();

    enum        stateType{ INIT, LOGIN, LOGGED, DISCONNECTED };
    stateType   state;

    QTcpSocket  socket;
    //! a QDataStream to read/write "CommPacket" to the client conected
    QDataStream stream;
    //! aQMutex to lock the read of the stream
    QMutex      readStream;
    //! aQMutex to lock the write of the stream
    QMutex      writeStream;

private slots:
    //! called when a packet may be present on the socket
    void packetAvailable();
    //! called by a thread when the reading is finished and another thread can be launched
    void readFinished();

private slots:
    //! if the connexion is closed, look if some thread are still running
    void tryToDelete();
    //! called when an ThreadPacket is destroyed
    void threadFinished();

private:
    //! lock the number of threads to MAX_USER_THREADS
    QSemaphore  threads;

//! to remove, just for debug message in cronstruct
public:
    quint32     id;
private:
    static quint32 nbCon;
};

#endif // CLIENTSOCKET_H
