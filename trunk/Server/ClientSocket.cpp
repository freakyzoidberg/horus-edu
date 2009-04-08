#include "ClientSocket.h"
#include "ThreadPacket.h"

ClientSocket::ClientSocket(int _socket)
{
    static quint32 newId = 0;
    id = newId++;
    qDebug() << "Client" << id << "connected";
    nbrThreads = 0;

    connect(&socket, SIGNAL(disconnected()), this, SLOT(tryToDelete()));
    connect(&socket, SIGNAL(readyRead()),    this, SLOT(packetReceived()));

    stream.setDevice(&socket);
    socket.setSocketDescriptor(_socket);

    CommInit ci(CURRENT_PROTO_VERSION, SERVER_NAME);
    stream << ci;
}

ClientSocket::~ClientSocket()
{
    qDebug() << "Client"<< id << "disconected.";
}

void ClientSocket::tryToDelete()
{
    if ( ! nbrThreads)
        deleteLater();
}

void ClientSocket::threadStart()
{
    mutex.lock();
    nbrThreads++;
    mutex.unlock();
}

void ClientSocket::threadFinished()
{
    mutex.lock();
    nbrThreads--;
    if ( ! nbrThreads && socket.state() == QTcpSocket::UnconnectedState && ! socket.bytesAvailable())
        deleteLater();
    mutex.unlock();
}

void ClientSocket::packetReceived()
{
    if (socket.bytesAvailable() > 0)
        QThreadPool::globalInstance()->start( new ThreadPacket(this) );
}
