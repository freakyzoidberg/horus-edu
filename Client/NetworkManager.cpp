#include "NetworkManager.h"
#include    "PluginManager.h"
#include <QSettings>


NetworkManager::NetworkManager(QObject *parent) : CommSocket()
{
    this->packManag = new PacketManager(parent);
    this->parent = static_cast<ClientApplication *>(parent);
    connect(this, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    connect(packManag, SIGNAL(sendPacket(const QByteArray&)), this, SLOT(sendPacket(const QByteArray&)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(disconnected()), this, SLOT(quit()));
    setObjectName("NetworkManager");
}

NetworkManager::~NetworkManager()
{
}

bool    NetworkManager::event(QEvent *e)
{
   if(e->type() == ClientEvents::StartEvent)
    {
        QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
        qDebug() << "NetworkManager: Recieve StartEvent";
        connectToHostEncrypted(settings.value("Network/Server").toString(), settings.value("Network/Port").toUInt());
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
         QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
         QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::NetworkErrorEvent));
         break;
     case QAbstractSocket::HostNotFoundError:
         qDebug() << "The host was not found. Please check the host name and port settings.";
         QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
         QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::NetworkErrorEvent));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         qDebug() << "The connection was refused by the peer. Make sure the Horus server is running, and check that the host name and port settings are correct.";
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::NetworkErrorEvent));
         break;
     default:
         qDebug() << tr("The following error occurred: %1.").arg(errorString());
     }
 }
