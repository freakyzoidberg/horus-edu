#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : CommSocket()
{
    this->packManag = new PacketManager(parent);
    connect(      this, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    connect(packManag, SIGNAL(sendPacket(const QByteArray&)),           this, SLOT(sendPacket(const QByteArray&)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(disconnected()),                      this, SLOT(quit()));
    setObjectName("NetworkManager");
}

bool    NetworkManager::event(QEvent *e)
{
   if(e->type() == ClientEvents::StartEvent)
    {
        qDebug() << "NetworkManager: Recieve StartEvent";
        connectToHostEncrypted("localhost", 42000);
        return true;
    }
    else if (e->type() == ClientEvents::SendPacketEvent)
    {
        qDebug() << "NetworkManager: Recieve Packet";
        packManag->PacketToSend(e);
        return true;
    }
    else if (e->type() == ClientEvents::SendLoginEvent)
    {
        qDebug() << "NetworkManager: Recieve SendLoginEvent";
        SendLoginEvent *spe = static_cast<SendLoginEvent *>(e);
        this->sendPacket(spe->pack);
        return true;
    }
    return QObject::event(e);
}

void    NetworkManager::quit()
{

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
         qDebug() << tr("The following error occurred: %1.").arg(errorString());
     }
 }
NetworkManager::~NetworkManager()
{
}
