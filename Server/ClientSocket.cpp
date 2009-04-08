#include "ClientSocket.h"
#include "Login.h"
#include "ThreadPacket.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    static quint32 newId = 0;
    id = newId++;
    qDebug() << "Client" << id << "connected";
    nbrThreads = 0;
    stream.setDevice(this);
}

ClientSocket::~ClientSocket()
{
    qDebug() << "Client"<< id << "disconected.";
    stream.setDevice(this);
}

void ClientSocket::packetRead()
{
    if (bytesAvailable())
        emit readyRead();
}

void ClientSocket::tryToDelete()
{
    if ( ! nbrThreads)
        deleteLater();
}

void ClientSocket::threadStart()
{
    nbrThreadsMutex.lock();
    nbrThreads++;
    nbrThreadsMutex.unlock();
}

void ClientSocket::threadFinished()
{
    nbrThreadsMutex.lock();
    nbrThreads--;
    nbrThreadsMutex.unlock();
    if ( ! nbrThreads && state() == UnconnectedState && ! bytesAvailable())
        deleteLater();
}
/*
void ClientSocket::onReceveInit()
{// TODO maybe need a thread here or possible to lock the server

    disconnect(this, SIGNAL(readyRead()), 0, 0);
    CommInit ci;
    stream >> ci;

    if (ci.protoVersion > CURRENT_PROTO_VERSION)
    {
        CommPacket pac(CommPacket::ERROR);
        stream << pac;
        return disconnectFromHost();
    }

    connect(this, SIGNAL(readyRead()), SLOT(onRecevePacket()));
    packetRead();
}
*/
void ClientSocket::onRecevePacket()
{
    threadStart();
    QThreadPool::globalInstance()->start( new ThreadPacket(this) );
}
