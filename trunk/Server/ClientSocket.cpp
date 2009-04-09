#include "ClientSocket.h"
#include "ThreadPacket.h"
#include "../Common/Defines.h"

ClientSocket::ClientSocket(int _socket)
{
    static quint32 newId = 0;
    id = newId++;
    qDebug() << "-----Client" << id << "connected";

    state = INIT;
    nbThreads = 0;

    //read
    connect(&socket, SIGNAL(readyRead()),      this, SLOT(packetAvailable()));
    connect(this,    SIGNAL(readFinishedSignal()),   SLOT(readFinishedSlot()));

    //delete
    connect(&socket, SIGNAL(disconnected()),   this, SLOT(tryToDelete()));
    connect(this,    SIGNAL(threadFinishedSignal()), SLOT(threadFinishedSlot()));

    stream.setDevice(&socket);
    socket.setSocketDescriptor(_socket);

    // Send the CommInit packet
    CommInit ci(CURRENT_PROTO_VERSION, SERVER_NAME);
    stream << ci;
}

ClientSocket::~ClientSocket()
{
    qDebug() << "-----Client"<< id << "disconected.";
}


//READ PART
void ClientSocket::readFinished() { emit readFinishedSignal(); }// for the thread
void ClientSocket::readFinishedSlot()
{
    readStream.unlock();
    if (socket.bytesAvailable() > 0)
        packetAvailable();
}

void ClientSocket::packetAvailable()
{
    if ( ! readStream.tryLock())
        return;

    nbThreads++;
    QThreadPool::globalInstance()->start( new ThreadPacket(this) );
}


//DELETE PART
void ClientSocket::threadFinished() { emit threadFinishedSignal(); }// for the thread
void ClientSocket::threadFinishedSlot()
{
    nbThreads--;
    if (socket.state() == QTcpSocket::UnconnectedState)
        tryToDelete();
}

void ClientSocket::tryToDelete()
{
    if ( ! nbThreads)
        deleteLater();
}
