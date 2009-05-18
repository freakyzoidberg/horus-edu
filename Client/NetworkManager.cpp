#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : CommSocket(parent)
{
    packManag = new PacketManager(this);
    connect(      this, SIGNAL(packetReceived(const QByteArray&)), packManag, SLOT(packetReceived(const QByteArray&)));
    connect(packManag, SIGNAL(sendPacket(const QByteArray&)),           this, SLOT(sendPacket(const QByteArray&)));
    connect(packManag, SIGNAL(lwState(bool)),           this, SLOT(lwState(bool)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(disconnected()),                      this, SLOT(quit()));
    setObjectName("NetworkManager");
    this->ld = new LoginDialog(this);
    this->ld->show();
    //this->start();
}

void run()
{
    //this->exec();
}
void    NetworkManager::lwState(bool st)
{
    if (st == true)
        ld->show();
    else
        ld->hide();
}

bool    NetworkManager::event(QEvent *e)
{
    if(e->type() == ClientEvents::StartEvent)
    {
        qDebug() << "NewtworkManager: Recieve StartEvent";
        connectToHostEncrypted("localhost", 42000);
        return true;
    }
    else if (e->type() == ClientEvents::SendPacketEvent)
    {
        qDebug() << "NewtworkManager: Recieve LoginEvent";
        packManag->PacketToSend(e);
        return true;
    }
    return true;
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

bool NetworkManager::instanceFlag = false;
NetworkManager* NetworkManager::single = NULL;
NetworkManager* NetworkManager::getInstance(QObject *parent)
{
    if(! instanceFlag)
    {
        single = new NetworkManager(parent);
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}
NetworkManager::~NetworkManager()
{
    instanceFlag = false;
}

bool    NetworkManager::quit()
{
    qDebug() << "Disconnected from server";
    return true;
}
