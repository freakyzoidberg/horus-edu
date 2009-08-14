#include "NetworkManager.h"

#include <QSettings>

#include "MetaManager.h"
#include "NotificationClient.h"


NetworkManager::NetworkManager() : CommSocket()
{
    this->packManag = new PacketManager();
    AbstractManager::QObject::connect((QObject *)(AbstractManager *)this, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    AbstractManager::QObject::connect(packManag, SIGNAL(sendPacket(const QByteArray&)), (QObject *)(AbstractManager *)this, SLOT(sendPacket(const QByteArray&)));
    AbstractManager::QObject::connect((QObject *)(AbstractManager *)this, SIGNAL(error(QAbstractSocket::SocketError)), (QObject *)(AbstractManager *)this, SLOT(displayError(QAbstractSocket::SocketError)));
    AbstractManager::QObject::connect((QObject *)(AbstractManager *)this, SIGNAL(disconnected()), (QObject *)(AbstractManager *)this, SLOT(quit()));
//    AbstractManager::QObject::setObjectName("NetworkManager");
}

NetworkManager::~NetworkManager()
{
}

bool    NetworkManager::event(QEvent *e)
{
   if(e->type() == ClientEvents::StartEvent)
    {
        QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
        if (settings.value("Network/Server").toString().isEmpty() == true || settings.value("Network/Port").toString().isEmpty() == true)
        {
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified("Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
        }
        else
        {
            qDebug() << "NetworkManager: Recieve StartEvent";
            connectToHostEncrypted(settings.value("Network/Server").toString(), settings.value("Network/Port").toUInt());
        }
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
    else if (e->type() == ClientEvents::OfflineModeEvent)
    {
        qDebug() << "NetworkManager: Recieve OfflineModeEvent";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
//        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//        QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
        this->disconnectFromHost();
        return true;
    }
	qDebug() << "NetworkManager::event: Received User Event not managed ! (Event.type=" << e->type() <<")";
	return (CommSocket::event(e));
}

void    NetworkManager::quit()
{
    qDebug() <<  "Disconnected from server";
}

void    NetworkManager::displayError(QAbstractSocket::SocketError socketError)
 {
    switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified("Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     case QAbstractSocket::HostNotFoundError:
         qDebug() << "The host was not found. Please check the host name and port settings.";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified("Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         qDebug() << "The connection was refused by the peer. Make sure the Horus server is running, and check that the host name and port settings are correct.";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified("Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     default:
         qDebug() << tr("The following error occurred: %1.").arg(errorString());
     }
 }
