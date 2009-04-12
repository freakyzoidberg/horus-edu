#include "ClientSocket.h"
#include "ThreadPacket.h"
#include "../Common/Defines.h"

quint32 ClientSocket::nbCon = 0;

ClientSocket::ClientSocket(int _socket)
{
    static quint32 newId = 0;
    nbCon++;
    id = newId++;
    qDebug() << "-----Client" << id << "connected";

    state = INIT;
    threads.release(MAX_USER_THREADS);

    connect(&socket, SIGNAL(readyRead()),      this, SLOT(packetAvailable()));
    connect(&socket, SIGNAL(disconnected()),   this, SLOT(tryToDelete()));
//    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)),   this, SLOT(socketError(QAbstractSocket::SocketError)));

    stream.setDevice(&socket);
    socket.setSocketDescriptor(_socket);

    // Send the CommInit packet
    CommInit ci(CURRENT_PROTO_VERSION, SERVER_NAME);
    stream << ci;
}

ClientSocket::~ClientSocket()
{
    nbCon--;
    qDebug() << "-----Client"<< id << "disconected. there's still" << nbCon << "users";
}

void ClientSocket::socketError(QAbstractSocket::SocketError e)
{
    qDebug() << e;
}

    void ClientSocket::readFinished()
{
    readStream.unlock();
    if (socket.bytesAvailable() > 0)
        packetAvailable();
}

void ClientSocket::packetAvailable()
{
    if ( ! readStream.tryLock())
        return;

    if ( ! threads.tryAcquire())
        return readStream.unlock();

    ThreadPacket* thread = new ThreadPacket(this);

    connect(thread, SIGNAL(readFinished()), this, SLOT(readFinished()));
    connect(thread, SIGNAL(destroyed()),    this, SLOT(threadFinished()));

    QThreadPool::globalInstance()->start(thread);
}


void ClientSocket::threadFinished()
{
    threads.release();
    if (socket.state() == QTcpSocket::UnconnectedState)
        tryToDelete();
}

void ClientSocket::tryToDelete()
{
    if (threads.available() == MAX_USER_THREADS)
        deleteLater();
}
