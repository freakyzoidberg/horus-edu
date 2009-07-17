#include "ThreadPlugin.h"

#include <QSettings>
#include <QPluginLoader>
#include <QDebug>
#include <QApplication>
#include <QMap>
#include "ClientEvents.h"
#include "../Common/Defines.h"
#include "../Common/Plugin.h"
#include "../Common/MetaPlugin.h"
#include "../Common/DataPlugin.h"
#include "DataManagerClient.h"

ThreadPlugin::ThreadPlugin(ClientApplication *parent) : QThread::QThread(parent)
{
    this->start();
}

bool    ThreadPlugin::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        PluginManagerClient::instance()->load();
//        this->loadPlugins();
        QApplication::postEvent(((ClientApplication*)parent())->loader, new QEvent(ClientEvents::StartEvent));
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        QApplication::postEvent(((ClientApplication*)parent())->loader, new QEvent(ClientEvents::StopEvent));
        this->exit(0);
        return (true);
    }
//    else if (event->type() == ClientEvents::PluginEvent)
//    {
//        //qDebug() << "step1";
//        PluginEvent *pe = static_cast<PluginEvent *>(event);
//
//
//        INetworkPlugin *networkP = this->findNetworkPlugin(pe->pTarget);
//        if (networkP != 0 )
//        {
//            //qDebug() << "step2";
//            networkP->recvPacket(pe->pack);
//        }
//        return (true);
//    }
    else
    {
        qDebug() << "ThreadPlugin: Received Event not managed";
        return (QThread::event(event));
    }
}

void    ThreadPlugin::run()
{
    exec();
}
