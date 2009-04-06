#include "ClientSocket.h"
#include "Login.h"
#include "ThreadPacket.h"

quint32 ClientSocket::newId = 1;

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    id = newId;
    newId++;
    qDebug() << "Client" << id << "connected";
    stream.setDevice(this);
}

void ClientSocket::onReceveInit()
{
    disconnect(this, SIGNAL(readyRead()), 0, 0);
    CommInit ci;
    stream >> ci;

    if (ci.protoVersion > CURRENT_PROTO_VERSION)
    {
        CommPacket pac(CommPacket::UNKNOW_PROTOCOL);
        stream << pac;
        return disconnectFromHost();
    }

    connect(this, SIGNAL(readyRead()), SLOT(onRecevePacket()));
    if (bytesAvailable())
        onRecevePacket();
}

void ClientSocket::onRecevePacket()
{
    QThreadPool::globalInstance()->start( new ThreadPacket(this) );
}

ClientSocket::~ClientSocket()
{
    qDebug() << "Client"<< id << "disconected.";
    stream.setDevice(this);
}
