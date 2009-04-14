#include "ClientSocket.h"
#include "ThreadPacket.h"
#include "../Common/Defines.h"

quint32 ClientSocket::nbCon = 0;

ClientSocket::ClientSocket(int _socket) : CommSocket()
{
    static quint32 newId = 0;
    nbCon++;
    id = newId++;
    qDebug() << "-----Client" << id << "connected";

    threads.release();//1
    nbThreads = 0;

    connect(this, SIGNAL(packetReceived(QByteArray)), this, SLOT(packetAvailable(QByteArray)));
    connect(this, SIGNAL(disconnected()),   this, SLOT(tryToDelete()));
//    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    setSocketDescriptor(_socket);

    // Send the CommInit packet
    CommInit init(CURRENT_PROTO_VERSION+42, SERVER_NAME);
    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;
}

ClientSocket::~ClientSocket()
{
    nbCon--;
    qDebug() << "-----Client"<< id << "disconected. there's still" << nbCon << "users";
    close();
}
/*
void ClientSocket::socketError(QAbstractSocket::SocketError e)
{
    qDebug() << e;
}
*/
void ClientSocket::packetAvailable(QByteArray pac)
{
    recvQueue.push_back(pac);
    tryToReadPacket();
}

void ClientSocket::tryToReadPacket()
{
    if ( ! recvQueue.length())
        return;

    if ( ! threads.tryAcquire())
        return;
    nbThreads++;

    ThreadPacket* thread = new ThreadPacket(this, recvQueue.first());
    recvQueue.pop_front();

    connect(thread, SIGNAL(destroyed()), this, SLOT(threadFinished()));

    QThreadPool::globalInstance()->start(thread);
    tryToReadPacket();
}

void ClientSocket::threadFinished()
{
    nbThreads--;
    threads.release();
    tryToReadPacket();
    if (state() == QTcpSocket::UnconnectedState)
        tryToDelete();
}

void ClientSocket::waitOtherThreads()
{
    while (threads.tryAcquire()) ;
    while (nbThreads > 1)
        threads.acquire();
}

void ClientSocket::allowOtherThreads()
{
    waitOtherThreads();
    threads.release(MAX_USER_THREADS - 1);
}

void ClientSocket::tryToDelete()
{
    if ( ! nbThreads && ! recvQueue.length())
        deleteLater();
}
