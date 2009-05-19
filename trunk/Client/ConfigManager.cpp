#include "ConfigManager.h"

ConfigManager::ConfigManager(QObject *parent) : QThread(parent)
{
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

void    ConfigManager::loadConfig()
{
}

void    ConfigManager::saveConfig()
{
}
