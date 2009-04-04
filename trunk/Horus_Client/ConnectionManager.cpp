#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    //tcpSocket = new QTcpSocket();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void    ConnectionManager::ConnectTo()
{
     tcpSocket->abort();
     tcpSocket->connectToHost("192.168.42.51", 4242);
}

void    ConnectionManager::readData()
{
     QDataStream in(tcpSocket);
     in.setVersion(QDataStream::Qt_4_0);

     if (blockSize == 0) {
         if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
             return;

         in >> blockSize;
     }

     if (tcpSocket->bytesAvailable() < blockSize)
         return;

     QString nextFortune;
     in >> nextFortune;

     if (nextFortune == currentFortune) {
         QTimer::singleShot(0, this, SLOT(ConnectTo()));
         return;
     }

     currentFortune = nextFortune;
}

void    ConnectionManager::writeData()
{

}

 void   ConnectionManager::displayError(QAbstractSocket::SocketError socketError)
 {
/*
     switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     case QAbstractSocket::HostNotFoundError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
     default:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The following error occurred: %1.")
                                  .arg(tcpSocket->errorString()));
     }*/
 }
