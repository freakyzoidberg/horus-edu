#include "PluginManagerClient.h"

#include <QSettings>
#include <QApplication>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

#include "../Common/MetaPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/DataPlugin.h"

#include "DataManagerClient.h"
#include "ClientEvents.h"

PluginManagerClient::PluginManagerClient()
{
	this->user = 0;
}

bool PluginManagerClient::event(QEvent *event)
{
	if (event->type() == ClientEvents::StartEvent)
	{
		this->loadPlugins();
		emit loaded(100);
		return (true);
	}
	return (PluginManager::event(event));
}

const QHash<QString, Plugin*>& PluginManagerClient::plugins() const
{
	return (this->_plugins);
}

UserData* PluginManagerClient::currentUser() const
{
	return (this->user);
}

void PluginManagerClient::setCurrentUser(UserData* _user)
{
	this->user = _user;
}

void PluginManagerClient::loadPlugins()
{
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
	QStringList	pluginsToLoad;
	QStringList	pluginFilter;

    settings.beginGroup("Plugins");
    QDir pluginsUserDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    QDir pluginsSystemDir(settings.value("SystemDirectoryPath", "/Undefined").toString());
    settings.endGroup();
	if ( ! pluginsUserDir.exists() && ! pluginsSystemDir.exists())
    {
		emit notified(Notification::ERROR, "No Plugin paths available.");
        return ;
    }
    if ( ! pluginsUserDir.exists())
		emit notified(Notification::WARNING, "User plugin path doesn't exist, please review your settings.");
    if ( ! pluginsSystemDir.exists())
		emit notified(Notification::WARNING, "System plugin path doesn't exist, please review your settings.");
#if defined(Q_OS_WIN)
# define PLUGIN_FILTER  "*.dll"
#elif defined(Q_OS_MAC)
# define PLUGIN_FILTER  "*.so" // ??
#else
# define PLUGIN_FILTER  "*.so"
#endif
	pluginFilter << PLUGIN_FILTER;
    if (pluginsUserDir.exists())
		foreach (QString filename, pluginsUserDir.entryList(pluginFilter))
			if (!pluginsToLoad.contains(filename))
				pluginsToLoad << filename;
    if (pluginsUserDir.exists())
		foreach (QString filename, pluginsUserDir.entryList(pluginFilter))
			if (!pluginsToLoad.contains(filename))
				pluginsToLoad << filename;
	foreach (QString filename, pluginsToLoad)
    {
        if (pluginsUserDir.exists() && pluginsUserDir.exists(filename))
            loadPlugin(filename, pluginsUserDir);
        else if (pluginsSystemDir.exists() && pluginsSystemDir.exists(filename))
            loadPlugin(filename, pluginsSystemDir);
    }
    foreach (Plugin* plugin, plugins())
        plugin->pluginManager = this;
    foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
        plugin->dataManager = new DataManagerClient(plugin);
	foreach (Plugin* plugin, plugins())
		QApplication::postEvent(plugin, new QEvent(ClientEvents::LoadPluginEvent));
}

bool    PluginManagerClient::loadPlugin(QString pluginName, QDir path)
{
    QPluginLoader loader(path.absoluteFilePath(pluginName));
    MetaPlugin *metaPlugin = qobject_cast<MetaPlugin*>(loader.instance());
    if (! metaPlugin)
    {
		emit notified(Notification::WARNING, loader.errorString());
        return (false);
    }
    foreach (Plugin* plugin, metaPlugin->pluginList)
    {
        _plugins.insert(plugin->pluginName(), plugin);
        qDebug() << "PluginManagerClient:" << plugin->pluginName() << "loaded from" << loader.fileName();
    }
    return (true);
}
