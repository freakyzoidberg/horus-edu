#include    "PluginManager.h"
#include    <QSettings>
#include    <QPluginLoader>
#include    "../Common/Defines.h"
#include    "StartEvent.h"
#include    "StopEvent.h"
#include    <QDebug>
#include    <QApplication>

PluginManager::PluginManager(QObject *parent) : QObject::QObject(parent)
{
}

bool    PluginManager::event(QEvent *event)
{
    if (event->type() == StartEvent::type)
    {
        qDebug() << "PluginManager: Receive StartEvent";
        this->loadPlugins();
        return (true);
    }
    else if (event->type() == StopEvent::type)
    {
        qDebug() << "PluginManager: Receive StopEvent";
        return (true);
    }
    else
    {
        qDebug() << "PluginManager: Receive Event not managed";
        return (false);
    }
}

void    PluginManager::loadPlugins()
{
    QSettings   settings;
    QDir        pluginsDir;
    QString     pluginName;
    QStringList plugins;

    settings.beginGroup("Plugins");
    pluginsDir = QDir(settings.value("DirectoryPath", "/Undefined").toString());
    if (pluginsDir.absolutePath() == "/Undefined")
    {
        pluginsDir = QDir(PREFIX);
        if (!pluginsDir.cd(QApplication::organizationName())
            || !pluginsDir.cd(QApplication::applicationName())
            || !pluginsDir.cd("Plugins"))
        {
            qDebug() << "PluginManager: Error: Plugin path doesn't exist.";
            return ;
        }
    }
    plugins = settings.value("Load", NULL).toStringList();
    foreach (pluginName, plugins)
    {
        loadPlugin(pluginName, pluginsDir);
    }
    settings.endGroup();
}

bool    PluginManager::loadPlugin(QString pluginName, QDir path)
{
    qDebug() << "PluginManager: Loading" << pluginName;
    QPluginLoader   loader(path.absoluteFilePath(pluginName));
    QObject         *plugin = loader.instance();
    IClientPlugin   *clientPlugin;
    QString         newPlugin;
    bool            success = true;

    if (findPlugin(pluginName))
        return (success);
    if (plugin)
    {
        clientPlugin = qobject_cast<IClientPlugin *>(plugin);
        if (clientPlugin)
        {
            foreach (newPlugin, clientPlugin->getPluginsRequired())
                success &= this->loadPlugin(newPlugin, path);
            if (success)
            {
                pluginsList.insert(pluginName, clientPlugin);
                qDebug() << "PluginManager: plugin" << pluginName << "loaded";
                foreach (newPlugin, clientPlugin->getPluginsRecommended())
                    this->loadPlugin(newPlugin, path);
                return (success);
            }
            qDebug() << "PluginManager: error while loading" << pluginName << ": Dependencies not satisfiables";
            loader.unload();
            return (false);
        }
    }
    qDebug() << "PluginManager: error while loading" << pluginName << ":" << loader.errorString();
    return (false);
}

QObject *PluginManager::findPlugin(QString &pluginName) const
{
    return pluginsList.value(pluginName);
}
