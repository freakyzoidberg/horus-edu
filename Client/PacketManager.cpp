#include "PacketManager.h"
#include "ClientApplication.h"
#include "../Common/PluginManager.h"
#include "../Common/NetworkPlugin.h"
#include "../Common/MetaPlugin.h"

PacketManager::PacketManager(QObject* parent) : QObject(parent)
{
    state = DISCONNECTED;
}

packetDirection PacketManager::packetDirections[] =
{
    0,//for CommPacket::UNDEFINED
    &PacketManager::PacketError,
    &PacketManager::PacketInit,
    &PacketManager::PacketAlive,
    &PacketManager::PacketLogin,
    &PacketManager::PacketData,
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
}

void PacketManager::PacketInit()
{
    CommInit i(packet);
    i.fromName = CLIENT_NAME;
    emit sendPacket(i.getPacket());

    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    settings.beginGroup("SESSIONS");
    if (settings.value("sessionLogin", "").toString() != "" && (settings.value("sessionEnd", 0).toUInt() > (QDateTime::currentDateTime().toTime_t() + 60) || settings.value("sessionTime", 0).toUInt() == 0))
    {
        state = PacketManager::LOGIN_SESSION;
        CommLogin  ls(CommLogin::LOGIN_SESSION);
        ls.login = settings.value("sessionLogin", "").toString();
        ls.sessionString = settings.value("sessionString", "").toByteArray();
        emit sendPacket(ls.getPacket());
    }
    else
    {
        state = INIT;
        QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::ShowLoginEvent));
    }
    settings.endGroup();

}

void PacketManager::PacketAlive()
{
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
        settings.endGroup();
        QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::HideLoginEvent));
        QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::StartEvent));
        state = PacketManager::LOGGED_IN;
        clearPacketStack();
    }
    else if (l.method == CommLogin::REFUSED)
    {
        QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::ShowLoginEvent));
    }

}

void PacketManager::PacketData()
{
    CommData data(packet);

    //TODO stock in QHash for quicker execution
    foreach (DataPlugin* plugin, PluginManager().findPlugins<DataPlugin*>())
        if (plugin->getDataType() == data.type)
            plugin->dataManager->receiveData(0, packet);
}

void PacketManager::PacketPlugin()
{
    CommPlugin p(packet);

    NetworkPlugin *plugin = PluginManager().findPlugin<NetworkPlugin*>( p.packet.targetPlugin );
    if (plugin)
        plugin->receivePacket(0, p.packet);
    //TODO else ... !!!
}

void        PacketManager::sessionEnd()
{
}
