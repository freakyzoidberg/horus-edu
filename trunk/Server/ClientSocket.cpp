#include "ClientSocket.h"
#include "Login.h"
#include "Request.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    stream.setDevice(this);
}

void ClientSocket::onRecvLogin()
{
    disconnect(this, SIGNAL(readyRead()), 0, 0);
    QThreadPool::globalInstance()->start( new Login(this) );
}

void ClientSocket::onRecvRequest()
{
    QThreadPool::globalInstance()->start( new Request(this) );
    // In case ther is another request in the queue
    if (bytesAvailable())
        emit readyRead();
}
