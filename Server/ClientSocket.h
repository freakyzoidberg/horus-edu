#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>
#include <QMutex>
#include <QObject>

#include "../Common/Defines.h"

class ClientSocket : public QObject
{
  Q_OBJECT

public:
    ClientSocket(int _socket);
    ~ClientSocket();

    QTcpSocket  socket;
    QDataStream stream;

    /*!
     * When a thread is created with an incoming packet, increment the number of threads
     * if the client is disconected,  we have to wait the end of all the threads before deleting it
     * these functions are thread safe!!!
     */
    void threadStart();
    void threadFinished();

    bool loginPassword(const QString& _login, const QByteArray& _sha1Pass);
    bool loginSession (const QString& _login, const QByteArray& _sessId);

public slots:
    void packetReceived();
    void tryToDelete();

private:
    QMutex  mutex;

    quint32 nbrThreads;
    QString login;

    quint32 id;//to remove, just for debug message in cronstruct
};

#endif // CLIENTSOCKET_H
