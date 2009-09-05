#include "NetworkManager.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDir>

#include "MetaManager.h"
#include "NotificationClient.h"

#include "PluginManagerClient.h"

NetworkManager::NetworkManager()
{
    this->packManag = new PacketManager();
    this->socket = new CommSocket();
    connect(socket, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    connect(packManag, SIGNAL(sendPacket(const QByteArray&)), socket, SLOT(sendPacket(const QByteArray&)));
    connect(PluginManagerClient::instance(), SIGNAL(sendPacket(const QByteArray&)), socket, SLOT(sendPacket(const QByteArray&)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(quit()));
    connect(packManag, SIGNAL(logged()), this, SLOT(log()));
    connect(packManag, SIGNAL(waitingUserPass()), this, SLOT(waitUserPass()));
}

bool    NetworkManager::event(QEvent *e)
{
   if(e->type() == ClientEvents::StartEvent)
    {
        QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
        if (settings.value("Network/Server").toString().isEmpty() == true || settings.value("Network/Port").toString().isEmpty() == true)
        {
			emit notified(Notification::WARNING, "Server's hostname or port unspecified, please review your settings.");
			QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
			emit loaded(100);
        }
        else
        {
            socket->connectToHostEncrypted(settings.value("Network/Server").toString(), settings.value("Network/Port").toUInt());
			emit loaded(15);
        }
        return (true);
    }
    else if (e->type() == ClientEvents::SendPacketEvent)
    {
        SendPacketEvent *spe = static_cast<SendPacketEvent *>(e);
        packManag->PacketToSend(spe->pack);
        return (true);
    }
    else if (e->type() == ClientEvents::OfflineModeEvent)
    {
		QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
        socket->disconnectFromHost();
		emit loaded(100);
        return (true);
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
	switch (socketError)
	{
     case QAbstractSocket::RemoteHostClosedError:
		 emit notified(Notification::WARNING, "Horus is unable to connect to server (Server closed the connexion), please review your settings and certificates.");
         break;
     case QAbstractSocket::HostNotFoundError:
		 emit notified(Notification::WARNING, "Horus is unable to connect to server (Server's hostname not found), please review your settings.");
         break;
     case QAbstractSocket::ConnectionRefusedError:
		 emit notified(Notification::WARNING, "Horus is unable to connect to server (Server refused the connexion), please review your settings and make sure that the server is running.");
         break;
     default:
		 emit notified(Notification::WARNING, "Horus is unable to connect to server (" + socket->errorString() + "), please review your settings.");
    }
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::OfflineModeEvent));
	emit loaded(100);
}

void NetworkManager::log()
{
	emit loaded(100);
}

void NetworkManager::waitUserPass()
{
	emit notified(Notification::LOGIN, "Please enter your username and password.");
}
