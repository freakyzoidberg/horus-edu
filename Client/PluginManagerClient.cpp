#include "PluginManagerClient.h"
#include "DataManagerClient.h"
#include "../Common/DataPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/MetaPlugin.h"
#include <QSettings>
#include <QApplication>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include "ClientEvents.h"

PluginManagerClient::PluginManagerClient()
{
}

bool PluginManagerClient::event(QEvent *event)
{
	if (event->type() == ClientEvents::StartEvent)
	{
		this->loadPlugins();
		emit loaded(100);
		return (true);
	}
	return (AbstractManager::event(event));
}

const QHash<QString, Plugin*>& PluginManagerClient::plugins() const { return _plugins;}

UserData* PluginManagerClient::currentUser() const { return user; }

void PluginManagerClient::setCurrentUser(UserData* _user) { user = _user; }

void PluginManagerClient::loadPlugins()
{
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);

    settings.beginGroup("Plugins");
    QDir pluginsUserDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    QDir pluginsSystemDir(settings.value("SystemDirectoryPath", "/Undefined").toString());

    if ( ! pluginsUserDir.exists())
        qDebug() << "ThreadPlugin: Warning User Plugin path doesn't exist.";
    if ( ! pluginsSystemDir.exists())
        qDebug() << "ThreadPlugin: Warning System Plugin path doesn't exist.";
    if ( ! pluginsUserDir.exists() && ! pluginsSystemDir.exists())
    {
        qDebug() << "ThreadPlugin: Error: No Plugin paths available.";
        return ;
    }

    foreach (QString pluginName, settings.value("Load").toStringList())
    {
        if (pluginsUserDir.exists())
            loadPlugin(pluginName, pluginsUserDir);
        if (pluginsSystemDir.exists())
            loadPlugin(pluginName, pluginsSystemDir);
    }
    settings.endGroup();

    foreach (Plugin* plugin, plugins())
        plugin->pluginManager = this;

    foreach (Plugin* plugin, plugins())
        QApplication::postEvent(plugin, new QEvent(ClientEvents::LoadPluginEvent));

    foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
        plugin->dataManager = new DataManagerClient(plugin);
}

bool    PluginManagerClient::loadPlugin(QString pluginName, QDir path)
{
    QPluginLoader loader( path.absoluteFilePath(pluginName) );
    MetaPlugin *metaPlugin = qobject_cast<MetaPlugin*>(loader.instance());
    if ( ! metaPlugin)
    {
        qDebug() << "ThreadPlugin:" << path.absoluteFilePath(pluginName) << loader.errorString();
        return false;
    }

    foreach (Plugin* plugin, metaPlugin->pluginList)
    {
        _plugins.insert(plugin->pluginName(), plugin);
        qDebug() << "ThreadPlugin:" << plugin->pluginName() << "loaded from" << loader.fileName();
    }
    return true;
}
