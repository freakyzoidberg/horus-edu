#include "PluginManagerClient.h"

#include <QSettings>
#include <QApplication>
#include <QPluginLoader>
#include <QStringList>
#include <QTranslator>

#include "../Common/MetaPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommPlugin.h"
#include "NetworkPlugin.h"
#include "MetaManager.h"
#include "ManagerThread.h"

#include "DataManagerClient.h"
#include "ClientEvents.h"

PluginManagerClient::PluginManagerClient()
{
	user = 0;
}

bool PluginManagerClient::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        loadPlugins();
        return true;
    }
    return PluginManager::event(event);
}

void PluginManagerClient::loadPlugins()
{
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
	QStringList	pluginsToLoad;
	QStringList	pluginFilter;
	int i = 0;

    settings.beginGroup("Plugins");
    QDir pluginsUserDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    QDir pluginsSystemDir(settings.value("SystemDirectoryPath", "/Undefined").toString());
    settings.endGroup();
	if ( ! pluginsUserDir.exists() && ! pluginsSystemDir.exists())
    {
		emit notified(Notification::ERROR, tr("No Plugin paths available."));
        return ;
    }
    if ( ! pluginsUserDir.exists())
		emit notified(Notification::WARNING, tr("User plugin path doesn't exist, please review your settings."));
    if ( ! pluginsSystemDir.exists())
		emit notified(Notification::WARNING, tr("System plugin path doesn't exist, please review your settings."));
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
		bool isLoaded = false;

        if (pluginsUserDir.exists() && pluginsUserDir.exists(filename))
            isLoaded = loadPlugin(filename, pluginsUserDir);
        else if (pluginsSystemDir.exists() && pluginsSystemDir.exists(filename))
            isLoaded = loadPlugin(filename, pluginsSystemDir);
		if (!isLoaded)
				pluginsToLoad.removeAll(filename);
		else
				++i;
		emit loaded(50 * i / pluginsToLoad.count());
    }
	// NetworkPlugin
	qRegisterMetaType<PluginPacket>("PluginPacket");
	foreach (NetworkPlugin* plugin, findPlugins<NetworkPlugin*>())
	{
		plugin->moveToThread(dynamic_cast<QThread *>(MetaManager::getInstance()->findManager("NetworkManager")));
		connect(plugin, SIGNAL(sendPacket(PluginPacket)), this, SLOT(sendPluginPacket(PluginPacket)));
	}
	// DataPlugin
	foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
	{
		plugin->dataManager = new DataManagerClient(plugin);
		//DataPlugins are also moved to the network thread, is it necessary to have a dedicated thread for them ?
		plugin->moveToThread(dynamic_cast<QThread *>(MetaManager::getInstance()->findManager("NetworkManager")));
	}
	// every Plugins
    i = 0;
    foreach (Plugin* plugin, _plugins)
    {
        plugin->pluginManager = this;
        if ( ! plugin->canLoad())
        {
            _plugins.remove(plugin->pluginName());
            delete plugin;
        }
        else
            plugin->load();
		++i;
		emit loaded(50 + 50 * i / _plugins.count());
    }
    if (!i)
            emit loaded(100);
}

bool    PluginManagerClient::loadPlugin(QString pluginName, QDir path)
{
	QTranslator *translator;
    QPluginLoader loader(path.absoluteFilePath(pluginName));
    MetaPlugin *metaPlugin = qobject_cast<MetaPlugin*>(loader.instance());
    if (! metaPlugin)
    {
        emit notified(Notification::WARNING, loader.errorString());
        return (false);
    }
	translator = new QTranslator();
    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
	translator->load(pluginName.left(pluginName.lastIndexOf(".")) + "_" + settings.value("Locale").toString(), settings.value("TranslationsDirectoryPath").toString());
	QCoreApplication::installTranslator(translator);
    foreach (Plugin* plugin, metaPlugin->pluginList)
        _plugins.insert(plugin->pluginName(), plugin);
    return (true);
}

void PluginManagerClient::sendPluginPacket(PluginPacket packet)
{
    NetworkPlugin* plugin = (NetworkPlugin*)(sender());

    packet.sourcePlugin = plugin->pluginName();
    packet.packetVersion = plugin->pluginVersion();

    emit sendPacket(CommPlugin(packet).getPacket());
}
