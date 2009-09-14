#include "PacketManager.h"

#include <QSettings>

#include "NetworkPlugin.h"
#include "../Common/MetaPlugin.h"
#include "../Common/UserDataPlugin.h"

#include "PluginManagerClient.h"
#include "MetaManager.h"

PacketManager::PacketManager()
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

void PacketManager::PacketToSend(const QByteArray& pack)
{
    packetStack.enqueue(pack);
    clearPacketStack();
}

void    PacketManager::clearPacketStack()
{
    if (packetStack.isEmpty() == false)
    {
        emit sendPacket(packetStack.dequeue());
        clearPacketStack();
    }
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
		emit waitingUserPass();
        //QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::ShowLoginEvent));
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
        QDateTime sessionEnd = l.sessionEnd;
        sessionEnd.addSecs(QDateTime::currentDateTime().secsTo(l.serverDateTime));
        settings.setValue("sessionEnd", sessionEnd);

        qDebug() << "PacketManager::PacketLogin seconds between client and server:" << QDateTime::currentDateTime().secsTo(l.serverDateTime);
        qDebug() << "PacketManager::PacketLogin end of session:" << sessionEnd;

        //QTimer::singleShot(sessionEnd - QDateTime::currentDateTime().addSecs(l.sessionTime).toTime_t(), this, SLOT(sessionEnd()));
        settings.endGroup();
        //QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::HideLoginEvent));
        //QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::StartEvent));
		emit logged();
        state = PacketManager::LOGGED_IN;
        clearPacketStack();
    }
    else if (l.method == CommLogin::REFUSED)
    {
		emit waitingUserPass();
        //QApplication::postEvent(((ClientApplication*)(QCoreApplication::instance()))->loader, new QEvent(ClientEvents::ShowLoginEvent));
    }

}

void PacketManager::PacketData()
{
    CommData data(packet);

    //TODO may be stored in a QHash for quicker execution
    foreach (DataPlugin* plugin, MetaManager::getInstance()->findManager<PluginManager *>()->findPlugins<DataPlugin*>())
        if (plugin->getDataType() == data.type)
        {
            // To register the UserData* type for Q_ARG(UserData*) just below. Don't ask me why...
            qRegisterMetaType<UserData*>("UserData*");
            QMetaObject::invokeMethod((QObject*)plugin->dataManager, "receiveData",
                                      Q_ARG(UserData*, MetaManager::getInstance()->findManager<PluginManager*>()->currentUser()),
                                      Q_ARG(const QByteArray, data.data)
                                      );
            return;
        }
    qDebug() << "PacketManager::PacketData() cannot find" << data.type << "plugin.";
}

void PacketManager::PacketPlugin()
{
    CommPlugin p(packet);

    NetworkPlugin *plugin = MetaManager::getInstance()->findManager<PluginManager *>()->findPlugin<NetworkPlugin*>( p.packet.targetPlugin );
    if ( ! plugin)
    {
        qDebug() << "PacketManager::PacketPlugin() cannot find" << p.packet.targetPlugin << "plugin.";
        return;
    }
    qRegisterMetaType<PluginPacket>("PluginPacket");
    QMetaObject::invokeMethod(plugin, "receivePacket", Qt::QueuedConnection, Q_ARG(PluginPacket, p.packet));
}

void        PacketManager::sessionEnd()
{
}
