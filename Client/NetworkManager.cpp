#include "NetworkManager.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDir>

#include "MetaManager.h"
#include "NotificationClient.h"


NetworkManager::NetworkManager()
{
    this->packManag = new PacketManager();
	this->socket = new CommSocket();
    connect(socket, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    connect(packManag, SIGNAL(sendPacket(const QByteArray&)), socket, SLOT(sendPacket(const QByteArray&)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(quit()));
	connect(packManag, SIGNAL(logged()), this, SLOT(log()));
	connect(packManag, SIGNAL(waitingUserPass()), this, SLOT(waitUserPass()));
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
			emit notified(Notification::WARNING, "Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
        }
        else
        {
            qDebug() << "NetworkManager: Recieve StartEvent";
            socket->connectToHostEncrypted(settings.value("Network/Server").toString(), settings.value("Network/Port").toUInt());
        }
        return true;
    }
    else if (e->type() == ClientEvents::SendPacketEvent)
    {
        qDebug() << "NetworkManager: Recieve Packet to send";
        SendPacketEvent *spe = static_cast<SendPacketEvent *>(e);
        packManag->PacketToSend(spe->pack);
        return true;
    }
    else if (e->type() == ClientEvents::SendLoginEvent)
    {
        qDebug() << "NetworkManager: Recieve SendLoginEvent to send";
        SendLoginEvent *sle = static_cast<SendLoginEvent *>(e);
        packManag->PacketToSend(sle->pack);
        return true;
    }
    else if (e->type() == ClientEvents::OfflineModeEvent)
    {
        qDebug() << "NetworkManager: Recieve OfflineModeEvent";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
//        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//        QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
        socket->disconnectFromHost();
        return true;
    }
	qDebug() << "NetworkManager::event: Received User Event not managed ! (Event.type=" << e->type() <<")";
	return (QObject::event(e));
}

void    NetworkManager::quit()
{
	//emit notified(Notification::ERROR, "Disconnected from server");
	//emit loaded(100);
    qDebug() <<  "Disconnected from server";
}

void    NetworkManager::displayError(QAbstractSocket::SocketError socketError)
 {
    switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified(Notification::WARNING, "Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     case QAbstractSocket::HostNotFoundError:
         qDebug() << "The host was not found. Please check the host name and port settings.";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified(Notification::WARNING, "Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         qDebug() << "The connection was refused by the peer. Make sure the Horus server is running, and check that the host name and port settings are correct.";
			emit loaded(100);
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit notified(Notification::WARNING, "Horus is unable to connect to server, please review your settings.");
//            QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
//            QApplication::postEvent(parent->findChild<ConfigManager *>(), new QEvent(ClientEvents::OfflineModeEvent));
//            QApplication::postEvent(parent->nC, new QEvent(ClientEvents::CServerEmptyEvent));
         break;
     default:
         qDebug() << tr("The following error occurred: %1.").arg(socket->errorString());
     }
 }

void NetworkManager::log()
{
	emit loaded(100);
}

void NetworkManager::waitUserPass()
{
	emit notified(Notification::LOGIN, "Please enter your username and password.");
}
