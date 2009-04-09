#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : QTcpSocket::QTcpSocket(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(quit()));
    this->packManag = new PacketManager(tcpSocket);
    this->setObjectName("NetworkManager");
}

void    NetworkManager::ConnectTo(QString addr, int port)
{
     tcpSocket->abort();
     tcpSocket->connectToHost(addr, port);
     stream.setDevice(tcpSocket);
}

void    NetworkManager::readData()
{
    if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
             return;

    stream >> protoPac;
    this->packManag->receivedData(protoPac);
    CommInit init;

    init.fromName = "Protocol Tester";
    stream << init;

    this->loginServer();

}

void    NetworkManager::loginServer()
{
    CommLogin  login;
    login.loginType = CommLogin::LOGIN_PASSWORD;
    login.login = "super-Menteur";
    login.sha1Pass = "4e1243bd22c66e76c2ba9eddc1f91394e57f9f83";
    stream << login;
    return;
}

void    NetworkManager::displayError(QAbstractSocket::SocketError socketError)
 {
    switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     case QAbstractSocket::HostNotFoundError:
         qDebug() << "The host was not found. Please check the host name and port settings.";
         break;
     case QAbstractSocket::ConnectionRefusedError:
         qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
         break;
     default:
         qDebug() << tr("The following error occurred: %1.").arg(tcpSocket->errorString());
     }
 }

bool    NetworkManager::quit()
{
    qDebug() << "Disconnected from server";
    return true;
}

bool    NetworkManager::event(QEvent *e)
{
    if(e->type() == StartEvent::type)
        qDebug() << "Recieved events";
    return true;
}
