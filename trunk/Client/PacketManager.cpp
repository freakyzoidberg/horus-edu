#include "PacketManager.h"

PacketManager::PacketManager(QObject* parent) : QObject(parent)
{
    this->parent = parent;
    state = DISCONNECTED;
}

packetDirection PacketManager::packetDirections[] =
{
    0,//for CommPacket::UNKNOW
    &PacketManager::PacketError,
    &PacketManager::PacketInit,
    &PacketManager::PacketAlive,
    &PacketManager::PacketLogin,
    &PacketManager::PacketFile,
    &PacketManager::PacketConfig,
    &PacketManager::PacketPlugin
};

void PacketManager::packetReceived(QByteArray p)
{
    packet = p;
    CommPacket pac(packet);
    if (pac.packetType != CommPacket::UNDEFINED)
        (this->*packetDirections[ pac.packetType ])();
}

void PacketManager::PacketError()
{
    CommError err(packet);
    qDebug() << "[ in]" << err;
}

void PacketManager::PacketInit()
{
    CommInit i(packet);
    qDebug() << "[ in]" << i;
    //TODO add protocol version compatible check
   // i.fromName = CLIENT_NAME;

   QApplication::postEvent(this->parent, new QEvent(ClientEvents::InitEvent));
   //emit sendPacket(i.getPacket());
    //qDebug() << "[ out]" << i;

    state = LOGGED_OUT;

    /*CommLogin l(packet);
    l.method = CommLogin::LOGIN_PASSWORD;
    l.login = "super-Menteur";
    l.sha1Pass = QByteArray::fromHex("0b9c2625dc21ef05f6ad4ddf47c5f203837aa32c");
    emit sendPacket(l.getPacket());
    qDebug() << "[out]" << l;*/
}

void PacketManager::PacketAlive()
{
    qDebug() << "[ in] Alive";
}

void PacketManager::PacketLogin()
{
    if (state != LOGGED_OUT)
        return;
    QSettings   settings;

    CommLogin l(packet);
    if (l.method == CommLogin::ACCEPTED)
    {
        settings.beginGroup("SESSIONS");
        QString session = l.sessionString.toHex();
        settings.setValue("sessionString", session);
        settings.setValue("sessionTime", l.sessionTime);
        settings.setValue("sessionEnd", QDateTime::currentDateTime().addSecs(l.sessionTime).toTime_t());
        qDebug() << "[ in]" << l;
        settings.endGroup();
    }
    else if (l.method == CommLogin::REFUSED)
    {
        qDebug() << "[ in]" << l;
    }

}

void PacketManager::PacketFile()
{
}

void PacketManager::PacketConfig()
{
}

void PacketManager::PacketPlugin()
{
}
