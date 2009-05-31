#include    "PluginManager.h"
#include    <QSettings>
#include    <QPluginLoader>
#include    "ClientEvents.h"
#include    "../Common/Defines.h"
#include    <QDebug>
#include    <QApplication>

PluginManager::PluginManager(ClientApplication *parent) : QThread::QThread(parent)
{
    this->parent = parent;
    this->start();
}

bool    PluginManager::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        qDebug() << "PluginManager: Receive StartEvent";
        this->loadPlugins();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        qDebug() << "PluginManager: Receive StopEvent";
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StopEvent));
        this->exit(0);
        return (true);
    }
    else
    {
        qDebug() << "PluginManager: Receive Event not managed";
        return (QThread::event(event));
    }
}

void    PluginManager::run()
{
    exec();
}

void    PluginManager::loadPlugins()
{
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    QDir        pluginsUserDir;
    QDir        pluginsSystemDir;
    QString     pluginName;
    QStringList plugins;

    settings.beginGroup("Plugins");
    pluginsUserDir = QDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    pluginsSystemDir = QDir(settings.value("SystemDirectoryPath", "/Undefined").toString());
    if (pluginsUserDir.absolutePath() == "/Undefined")
        qDebug() << "PluginManager: Warning User Plugin path doesn't exist.";
    if (pluginsSystemDir.absolutePath() == "/Undefined")
        qDebug() << "PluginManager: Warning System Plugin path doesn't exist.";
    if (pluginsUserDir.absolutePath() == "/Undefined" && pluginsSystemDir.absolutePath() == "/Undefined")
    {
        qDebug() << "PluginManager: Error: No Plugin paths available.";
        return ;
    }
    plugins = settings.value("Load", QStringList()).toStringList();
    foreach (pluginName, plugins)
        loadPlugin(pluginName, pluginsUserDir, pluginsSystemDir);
    settings.endGroup();
}

bool    PluginManager::loadPlugin(QString pluginName, QDir userPath, QDir systemPath)
{
    qDebug() << "PluginManager: Loading" << pluginName;
    QPluginLoader   *loader;
    QObject         *plugin;
    IClientPlugin   *clientPlugin;
    QString         newPlugin;
    bool            success;

    success = true;
    if (findPlugin(pluginName))
        return (success);
    loader = new QPluginLoader(userPath.absoluteFilePath(pluginName));
    plugin = loader->instance();
    qDebug() << "PluginManager: error while loading" << pluginName << ":" << loader->errorString();
    if (!plugin)
    {
        delete loader;
        loader = new QPluginLoader(systemPath.absoluteFilePath(pluginName));
        plugin = loader->instance();
    }
    if (plugin)
    {
        clientPlugin = qobject_cast<IClientPlugin *>(plugin);
        if (clientPlugin)
        {
            foreach (newPlugin, clientPlugin->getPluginsRequired())
                success &= this->loadPlugin(newPlugin, userPath, systemPath);
            if (success)
            {
                pluginsList.insert(pluginName, clientPlugin);
                qDebug() << "PluginManager: plugin" << pluginName << "loaded";
                foreach (newPlugin, clientPlugin->getPluginsRecommended())
                    this->loadPlugin(newPlugin, userPath, systemPath);
                QApplication::postEvent(parent->loader, new QEvent(ClientEvents::LoadPluginEvent));
                delete loader;
                return (success);
            }
            qDebug() << "PluginManager: error while loading" << pluginName << ": Dependencies not satisfiables";
            loader->unload();
            delete loader;
            return (false);
        }
    }
    qDebug() << "PluginManager: error while loading" << pluginName << ":" << loader->errorString();
    delete loader;
    return (false);
}

QObject *PluginManager::findPlugin(QString &pluginName) const
{
    return pluginsList.value(pluginName);
}
