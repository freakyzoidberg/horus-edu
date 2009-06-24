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

Q_DECL_EXPORT QHash<QString,Plugin*> PluginManager::_plugins;
//const QHash<QString,Plugin*>& PluginManager::plugins() const
//{
//    return _plugins;
//}

ThreadPlugin::ThreadPlugin(ClientApplication *parent) : QThread::QThread(parent)
{
    this->start();
}

bool    ThreadPlugin::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        this->loadPlugins();
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

void    ThreadPlugin::loadPlugins()
{
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);

    settings.beginGroup("Plugins");
    QDir pluginsUserDir = QDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    QDir pluginsSystemDir = QDir(settings.value("SystemDirectoryPath", "/Undefined").toString());
    settings.endGroup();

    if (pluginsUserDir.absolutePath() == "/Undefined")
        qDebug() << "ThreadPlugin: Warning User Plugin path doesn't exist.";
    if (pluginsSystemDir.absolutePath() == "/Undefined")
        qDebug() << "ThreadPlugin: Warning System Plugin path doesn't exist.";
    if (pluginsUserDir.absolutePath() == "/Undefined" && pluginsSystemDir.absolutePath() == "/Undefined")
    {
        qDebug() << "ThreadPlugin: Error: No Plugin paths available.";
        return ;
    }

    foreach (QString pluginName, settings.value("Load", QStringList()).toStringList())
    {
        loadPlugin(pluginName, pluginsUserDir);
        loadPlugin(pluginName, pluginsSystemDir);
    }

    foreach (Plugin* plugin, PluginManager().findPlugins<Plugin*>())
        QApplication::postEvent(plugin, new QEvent(ClientEvents::LoadPluginEvent));
}

bool    ThreadPlugin::loadPlugin(QString pluginName, QDir path)
{
    QPluginLoader   loader( path.absoluteFilePath(pluginName) );
    MetaPlugin *metaPlugin = qobject_cast<MetaPlugin*>(loader.instance());
    if ( ! metaPlugin)
    {
        qDebug() << "ThreadPlugin: error while loading" << pluginName << ":" << loader.errorString();
        return false;
    }

    foreach (Plugin* plugin, metaPlugin->pluginList)
    {
        _plugins.insert(plugin->pluginName(), plugin);
        qDebug() << "ThreadPlugin:" << plugin->pluginName() << "loaded from" << loader.fileName();
    }
    return true;;
}
