#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>
#include <QMutex>

//! there is one ClientSocket for each connexion
class ClientSocket : public QObject
{
  Q_OBJECT
//  Q_ENUMS(stateType)

public:
    //! Construct called by "Server"
    /*!
      * \param _socket the integer file descriptor given by Server::incommingConexion()
      */
    ClientSocket(int _socket);
    ~ClientSocket();

    enum        stateType{ INIT, LOGIN, LOGGED, DISCONNECTED };

    stateType   state;

    //! the QTcpSocket coresponding to the
    QTcpSocket  socket;
    //! a QDataStream to read/write "CommPacket" to the client conected
    QDataStream stream;
    //! aQMutex to lock the read of the stream
    QMutex      readStream;
    //! aQMutex to lock the write of the stream
    QMutex      writeStream;

//    User        user;


public:
    //! the method called by a thread to unlock the socket for reading
    void readFinished();
private slots:
    void packetAvailable();
    void readFinishedSlot();
signals:
    void readFinishedSignal();
private:
    quint32     nbThreads;


public:
    //! the method called by a thread to delete the ClientSocket if it's deconnected during the execution of the thread
    void threadFinished();
private slots:
    void tryToDelete();
    void threadFinishedSlot();
signals:
    void threadFinishedSignal();


public:
    //! to remove, just for debug message in cronstruct
    quint32     id;
};

#endif // CLIENTSOCKET_H
