#include "ConfigManager.h"

#include <QSettings>
#include <QDir>
#include <QString>
#include <QDebug>

#include "ClientEvents.h"
#include "../Common/Defines.h"

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
        this->loadConfig();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        qDebug() << "ConfigManager: Receive StopEvent";
        this->saveConfig();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StopEvent));
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
    QSettings settings;
    QDir      pluginsDir;
    QString   path;

    if (!settings.contains("Version"))
        settings.setValue("Version", CLIENT_VERSION);
    if (!settings.contains("Plugins/DirectoryPath"))
    {
        path = PREFIX + QApplication::organizationName() + "/" + QApplication::applicationName() + "/Plugins";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Plugins Directory." << path;
            if (!pluginsDir.mkdir(path))
                qDebug() << "ConfigManager: Unable to create Plugins path (not the rights ?).";
            else
                settings.setValue("Plugins/DirectoryPath", path);
        }
        else
            settings.setValue("Plugins/DirectoryPath", path);
    }
    settings.sync();
}

void    ConfigManager::loadConfig()
{
}

void    ConfigManager::saveConfig()
{
}
