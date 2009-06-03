#include "PacketManager.h"

#include "FileManager.h"

//test Git
#include "NetFile.h"

PacketManager::PacketManager(QObject* parent) : QObject()
{
    this->parent = static_cast<ClientApplication *>(parent);
    state = DISCONNECTED;
}

packetDirection PacketManager::packetDirections[] =
{
    0,//for CommPacket::UNDEFINED
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
    clearPacketStack();
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
    if (settings.value("sessionLogin", "").toString() != "" && (settings.value("sessionEnd", 0).toUInt() > (QDateTime::currentDateTime().toTime_t() + 60) || settings.value("sessionTime", 0).toUInt() == 0))
    {
        state = PacketManager::LOGIN_SESSION;
        CommLogin  ls(CommLogin::LOGIN_SESSION);
        ls.login = settings.value("sessionLogin", "").toString();
        ls.sessionString = settings.value("sessionString", "").toByteArray();
        emit sendPacket(ls.getPacket());
        qDebug() << "[out]" << ls;
    }
    else
    {
        state = INIT;
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::ShowLoginEvent));
    }
    settings.endGroup();

}

void PacketManager::PacketAlive()
{
    qDebug() << "[ in] Alive";
}

void PacketManager::PacketLogin()
{
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
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::HideLoginEvent));
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        state = PacketManager::LOGGED_IN;
        clearPacketStack();

        ///test de GIT, ne pas virer de suite
//        NetFile* file = FileManager::globalInstance()->getFile(1);
//        file->open(QIODevice::ReadOnly);
    }
    else if (l.method == CommLogin::REFUSED)
    {
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::ShowLoginEvent));
        qDebug() << "[ in]" << l;
    }

}

void PacketManager::PacketFile()
{
    FileManager::globalInstance()->receiveFilePacket(packet);
}

void PacketManager::PacketSettings()
{
//    CommSettings set(packet);
    RecvPacketEvent *rpe = new RecvPacketEvent(packet);
    QApplication::postEvent(parent->findChild<ConfigManager *>(), rpe);
}

void PacketManager::PacketPlugin()
{
    CommPlugin p(packet);

    this->pM = parent->findChild<PluginManager *>();
    QString target(p.packet.targetPlugin);
    if (this->pM->findPlugin(target) != 0)
    {
        PluginEvent *pe = new PluginEvent(p.packet);
        QApplication::postEvent(this->pM, pe);
    }
}

void        PacketManager::sessionEnd()
{

}
