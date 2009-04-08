#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>
#include <QMutex>

#include "../Common/Defines.h"

class ClientSocket : public QTcpSocket
{
  Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);
    ~ClientSocket();
    QDataStream stream;

    /*!
     * When a thread is created with an incoming packet, increment the number of threads
     * if the client is disconected,  we have to wait the end of all the threads before deleting it
     */
    //thread safe!!!
    void threadStart();
    void threadFinished();

public slots:
    void onRecevePacket();

    /*!
     * When a packet is read, allow the socket to launch another thread if there is another packet in queue
     */
    void packetRead();

    void tryToDelete();

private:
    quint32 nbrThreads;
    QMutex  nbrThreadsMutex;

    quint32 id;
};

#endif // CLIENTSOCKET_H
