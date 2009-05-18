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

void PacketManager::PacketToSend(QEvent *e)
{
    SendPacketEvent *spe = static_cast<SendPacketEvent *>(e);
    emit sendPacket(spe->pack);
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
    i.fromName = CLIENT_NAME;
    emit sendPacket(i.getPacket());
    qDebug() << "[ out]" << i;


    QSettings settings;
    settings.beginGroup("SESSIONS");
    if (settings.value("sessionEnd", 0).toUInt() > (QDateTime::currentDateTime().toTime_t() + 60))
    {
        CommLogin  ls(CommLogin::LOGIN_SESSION);
        ls.login = settings.value("sessionLogin", "").toString();
        ls.sessionString = settings.value("sessionString", "").toByteArray();
        emit sendPacket(ls.getPacket());
        qDebug() << "[out]" << ls;
    }
    else
    {
        emit lwState(true);
    }
    settings.endGroup();
    state = LOGGED_OUT;
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
        settings.setValue("sessionString", l.sessionString);
        settings.setValue("sessionTime", l.sessionTime);
        settings.setValue("sessionEnd", QDateTime::currentDateTime().addSecs(l.sessionTime).toTime_t());
        qDebug() << "[ in]" << l;
        settings.endGroup();
        emit lwState(false);
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
