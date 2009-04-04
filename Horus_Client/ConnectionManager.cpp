#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}
void    ConnectionManager::ConnectTo()
{
     tcpSocket->abort();
     tcpSocket->connectToHost(hostLineEdit->text(), portLineEdit->text().toInt());
}

void    ConnectionManager::readData()
{

}

void    ConnectionManager::writeData()
{

}
