#include "PacketManager.h"

PacketManager::PacketManager(QObject* parent) : QObject(parent)
{
    this->parent = static_cast<ClientApplication *>(parent);
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
    &PacketManager::PacketSettings,
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
    packetStack.enqueue(spe->pack);
}

void    PacketManager::clearPacketStack()
{
    if (state == PacketManager::LOGGED_IN)
    {
        if (packetStack.isEmpty() == false)
        {
            emit sendPacket(packetStack.dequeue());
            clearPacketStack();
        }
        return;
    }
    return;
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


    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
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
    state = INIT;
}

void PacketManager::PacketAlive()
{
    qDebug() << "[ in] Alive";
}

void PacketManager::PacketLogin()
{
    if (state != INIT)
        return;
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);

    CommLogin l(packet);

    if (l.method == CommLogin::ACCEPTED)
    {
        settings.beginGroup("SESSIONS");
        settings.setValue("sessionString", l.sessionString);
        settings.setValue("sessionTime", l.sessionTime);
        uint sessionEnd = QDateTime::currentDateTime().addSecs(l.sessionTime).toTime_t();
        settings.setValue("sessionEnd", sessionEnd);
        //QTimer::singleShot(sessionEnd - QDateTime::currentDateTime().addSecs(l.sessionTime).toTime_t(), this, SLOT(sessionEnd()));
        qDebug() << "[ in]" << l;
        settings.endGroup();
        emit lwState(false);
        state = PacketManager::LOGGED_IN;
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        clearPacketStack();
    }
    else if (l.method == CommLogin::REFUSED)
    {
        qDebug() << "[ in]" << l;
    }

}

void PacketManager::PacketFile()
{
}

void PacketManager::PacketSettings()
{
    CommSettings set(packet);
    RecvPacketEvent *rpe = new RecvPacketEvent(set.getPacket());
    ConfigManager   *configManager;
    configManager = parent->findChild<ConfigManager *>();
    QApplication::postEvent(configManager, rpe);
}

void PacketManager::PacketPlugin()
{
}

void        PacketManager::sessionEnd()
{

}
