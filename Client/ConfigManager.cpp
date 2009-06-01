#include "ConfigManager.h"

#include <QSettings>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QHash>

#include "ClientEvents.h"
#include "../Common/Defines.h"
#include "../Common/CommSettings.h"
#include "ThreadNetwork.h"
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
        this->sendLoadConfig();
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        this->saveConfig();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StopEvent));
        this->exit(0);
        return (true);
    }
    else if (event->type() == ClientEvents::RecvPacketEvent)
    {
        RecvPacketEvent *recvEvent;

        recvEvent = static_cast<RecvPacketEvent *>(event);
        this->recvLoadConfig(recvEvent->pack);
        return (true);
    }
    else if (event->type() == ClientEvents::NetworkErrorEvent)
    {
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        return (true);
    }
    else
    {
        qDebug() << "ConfigManager: Received Event not managed";
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
    CommSettings    SystemPacket;
    CommSettings    UserPacket;

    SystemPacket.method = CommSettings::GET;
    SystemPacket.scope = CommSettings::CLIENT_SYSTEM_SCOPE;
    SystemPacket.plugin = 0;
    UserPacket.method = CommSettings::GET;
    UserPacket.scope = CommSettings::CLIENT_USER_SCOPE;
    UserPacket.plugin = 0;
    ClientApplication::postEvent(ThreadNetwork::getInstance(this->parent), new SendPacketEvent(SystemPacket.getPacket()));
    ClientApplication::postEvent(ThreadNetwork::getInstance(this->parent), new SendPacketEvent(UserPacket.getPacket()));
}

void    ConfigManager::recvLoadConfig(QByteArray data)
{
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    CommSettings    packet(data);
    QHash<QString, QVariant> config;

    if (packet.scope == CommSettings::CLIENT_USER_SCOPE)
    {
        config = packet.getVariantSettings().toHash();
        if (config.contains("Plugins/Load"))
            settings.setValue("Plugins/Load", config.value("Plugins/Load"));
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
    }
}

void    ConfigManager::saveConfig()
{
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    CommSettings    UserPacket;
    QHash<QString, QVariant> config;

    UserPacket.method = CommSettings::SET;
    UserPacket.scope = CommSettings::CLIENT_USER_SCOPE;
    UserPacket.plugin = 0;
    config.insert("Plugins/Load", settings.value("Load"));
    UserPacket.setVariantSettings(config);
    ClientApplication::postEvent(ThreadNetwork::getInstance(this->parent), new SendPacketEvent(UserPacket.getPacket()));
}
