#include    "PluginManager.h"
#include    <QSettings>
#include    <QPluginLoader>
#include    "ClientEvents.h"
#include    "../Common/Defines.h"
#include    <QDebug>
#include    <QApplication>
#include    "InterfaceClient.h"
#include    "InterfaceNetwork.h"
#include    "InterfaceDisplay.h"
#include    "InterfaceFile.h"

PluginManager::PluginManager(ClientApplication *parent) : QThread::QThread(parent)
{
    this->parent = parent;
    this->start();
}

bool    PluginManager::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        this->loadPlugins();
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StartEvent));
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        QApplication::postEvent(parent->loader, new QEvent(ClientEvents::StopEvent));
        this->exit(0);
        return (true);
    }
    else
    {
        qDebug() << "PluginManager: Received Event not managed";
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
    INetworkPlugin  *networkPlugin;
    IDisplayablePlugin  *displayablePlugin;
    IFilePlugin  *filePlugin;
    QString         newPlugin;
    bool            success;

    success = true;
    if (findPlugin(pluginName))
        return (success);
    loader = new QPluginLoader(userPath.absoluteFilePath(pluginName));
    plugin = loader->instance();
    if (!plugin)
    {
        qDebug() << "PluginManager: error while loading" << pluginName << ":" << loader->errorString();
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
                clientPlugin->client = new InterfaceClient(clientPlugin, this->parent);
                pluginsList.insert(pluginName, clientPlugin);
                networkPlugin = qobject_cast<INetworkPlugin *>(clientPlugin);
                if (networkPlugin)
                {
                    networkPlugin->network = new InterfaceNetwork();
                    networkPluginsList.insert(pluginName, networkPlugin);
                }
                displayablePlugin = qobject_cast<IDisplayablePlugin *>(clientPlugin);
                if (displayablePlugin)
                {
                    displayablePlugin->display = new InterfaceDisplay();
                    displayablePluginsList.insert(pluginName, displayablePlugin);
                }
                filePlugin = qobject_cast<IFilePlugin *>(clientPlugin);
                if (filePlugin)
                {
                    filePlugin->file = new InterfaceFile();
                    filePluginsList.insert(pluginName, filePlugin);
                }
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

IClientPlugin *PluginManager::findPlugin(QString &pluginName) const
{
    return pluginsList.value(pluginName);
}

INetworkPlugin *PluginManager::findNetworkPlugin(QString &pluginName) const
{
    return networkPluginsList.value(pluginName);
}

IDisplayablePlugin *PluginManager::findDisplayablePlugin(QString &pluginName) const
{
    return displayablePluginsList.value(pluginName);
}

IFilePlugin *PluginManager::findFilePlugin(QString &pluginName) const
{
    return filePluginsList.value(pluginName);
}
