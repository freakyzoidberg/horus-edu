#include "ConfigManager.h"

#include <QSettings>
#include <QDir>
#include <QString>
#include <QDebug>

#include "ClientEvents.h"
#include "../Common/Defines.h"
#include "../Common/CommSettings.h"
#include "NetworkManager.h"
#include "ClientEvents.h"

ConfigManager::ConfigManager(ClientApplication *parent) : QThread(parent)
{
    this->parent = parent;
    this->createConfig();
    this->start();
}

bool    ConfigManager::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        qDebug() << "ConfigManager: Receive StartEvent";
        this->sendLoadConfig();
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        qDebug() << "ConfigManager: Receive StopEvent";
        this->saveConfig();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StopEvent));
        return (true);
    }
    else if (event->type() == ClientEvents::RecvPacketEvent)
    {
        RecvPacketEvent *recvEvent;

        recvEvent = static_cast<RecvPacketEvent *>(event);
        this->recvLoadConfig(recvEvent->pack);
        return (true);
    }
    else
    {
        qDebug() << "ConfigManager: Receive Event not managed";
        return (QThread::event(event));
    }
}

void    ConfigManager::run()
{
    exec();
}

void    ConfigManager::createConfig()
{
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    QDir      pluginsDir;
    QString   path;

    if (!settings.contains("Version"))
        settings.setValue("Version", CLIENT_VERSION);
    if (!settings.contains("Plugins/UserDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Plugins";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Plugins User Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("Plugins/UserDirectoryPath", path);
        }
        else
            settings.setValue("Plugins/UserDirectoryPath", path);
    }
    if (!settings.contains("Plugins/SystemDirectoryPath"))
    {
        path = PREFIX + QApplication::organizationName() + "/" + QApplication::applicationName() + "/Plugins";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Plugins System Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("Plugins/SystemDirectoryPath", path);
        }
        else
            settings.setValue("Plugins/SystemDirectoryPath", path);
    }
    settings.sync();
}

void    ConfigManager::sendLoadConfig()
{
    CommSettings    *UserPacket;
    CommSettings    *SystemPacket;
    NetworkManager  *networkManager;

    SystemPacket = new CommSettings;
    SystemPacket->method = CommSettings::GET;
    SystemPacket->scope = CommSettings::CLIENT_SYSTEM_SCOPE;
    SystemPacket->plugin = 0;
    UserPacket = new CommSettings;
    UserPacket->method = CommSettings::GET;
    UserPacket->scope = CommSettings::CLIENT_USER_SCOPE;
    UserPacket->plugin = 0;
    networkManager = this->parent->findChild<NetworkManager *>();
    ClientApplication::postEvent(networkManager, new SendPacketEvent(SystemPacket->getPacket()));
    ClientApplication::postEvent(networkManager, new SendPacketEvent(UserPacket->getPacket()));
}

void    ConfigManager::recvLoadConfig(QByteArray data)
{
    CommSettings    *packet;

    packet = new CommSettings(data);
    qDebug() << "Received settings:" << packet;
}

void    ConfigManager::saveConfig()
{
}
