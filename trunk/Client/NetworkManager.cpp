#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : CommSocket(parent)
{
    connect(      this, SIGNAL(packetReceived(QByteArray)), &packManag, SLOT(packetReceived(QByteArray)));
    connect(&packManag, SIGNAL(sendPacket(QByteArray)),           this, SLOT(sendPacket(QByteArray)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(disconnected()),                      this, SLOT(quit()));
    setObjectName("NetworkManager");
    //this->start();
}

 NetworkManager::~NetworkManager()
 {
        instanceFlag = false;
 }

bool NetworkManager::instanceFlag = false;
NetworkManager* NetworkManager::single = NULL;
NetworkManager* NetworkManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new NetworkManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void run()
{
    //this->exec();
}
/*
void    NetworkManager::ConnectTo(QString addr, int port)
{
     abort();
     connectToHost(addr, port);
}
*/
/*
void    NetworkManager::packetAvailable()
{
    if ( ! recvQueue.length())
        return;

    packManag.packetReceived(recvQueue.first());
    recvQueue.pop_front();

    //in case ther is another packet in the queue
    emit packetReceived();
}
*/
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
         qDebug() << tr("The following error occurred: %1.").arg(errorString());
     }
 }

bool    NetworkManager::quit()
{
    qDebug() << "Disconnected from server";
    return true;
}

void NetworkManager::login(const QString &login, const QString &pass)
{

}

bool    NetworkManager::event(QEvent *e)
{
    if(e->type() == StartEvent::type)
    {
        qDebug() << "NewtworkManager: Recieve StartEvent";
        connectToHostEncrypted("localhost", 42000);
    }
    return true;
}
