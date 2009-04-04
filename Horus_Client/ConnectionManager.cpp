#include "ConnectionManager.h"

ConnectionManager::ConnectionManager()
{
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void    ConnectionManager::ConnectTo(QString addr, int port)
{
     tcpSocket->abort();
     tcpSocket->connectToHost(addr, port);
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
     QMessageBox msgBox;
    msgBox.setText(currentFortune);
    msgBox.exec();
}

void    ConnectionManager::writeData()
{

}

 void   ConnectionManager::displayError(QAbstractSocket::SocketError socketError)
 {
     QMessageBox msgBox;


     switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     case QAbstractSocket::HostNotFoundError:
         msgBox.setText("The host was not found. Please check the "
                                     "host name and port settings.");
         break;
     case QAbstractSocket::ConnectionRefusedError:
         msgBox.setText("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct.");
         break;
     default:
         msgBox.setText(tr("The following error occurred: %1.")
                                  .arg(tcpSocket->errorString()));
     }
      msgBox.exec();
 }
