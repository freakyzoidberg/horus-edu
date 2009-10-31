#include "PluginManagerClient.h"

#include <../Common/LocalSettings.h>
#include <QApplication>
#include <QPluginLoader>
#include <QTranslator>
#include <QDebug>

#include "../Common/MetaPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommPlugin.h"
#include "NetworkPlugin.h"

#include "DataManagerClient.h"

#include "SecondaryThread.h"

PluginManagerClient* PluginManagerClient::instance()
{
	static PluginManagerClient* _instance = 0;
	if ( ! _instance)
	{
		_instance = new PluginManagerClient;
		_instance->moveToThread(SecondaryThread::instance());
	}
	return _instance;
}

void PluginManagerClient::loadPlugins()
{
	LocalSettings settings;
	QStringList	pluginsToLoad;
	QStringList	pluginFilter;

    settings.beginGroup("Plugins");
    QDir pluginsUserDir(settings.value("UserDirectoryPath", "/Undefined").toString());
    QDir pluginsSystemDir(settings.value("SystemDirectoryPath", "/Undefined").toString());
    settings.endGroup();
	if ( ! pluginsUserDir.exists() && ! pluginsSystemDir.exists())
		qCritical() << tr("No Plugin paths available.");
    if ( ! pluginsUserDir.exists())
		qWarning() << tr("User plugin path doesn't exist, please review your settings.");
    if ( ! pluginsSystemDir.exists())
		qWarning() << tr("System plugin path doesn't exist, please review your settings.");
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

	int i = 0;
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

		emit loadProgressChange(50 * i / pluginsToLoad.count());
    }

	QThread* secondaryThread = SecondaryThread::instance();

	qRegisterMetaType<PluginPacket>("PluginPacket");
	// NetworkPlugin
	foreach (NetworkPlugin* plugin, findPlugins<NetworkPlugin*>())
	{
		plugin->moveToThread(secondaryThread);
		connect(plugin, SIGNAL(sendPacket(PluginPacket)), this, SLOT(sendPluginPacket(PluginPacket)));
	}
	// DataPlugin
	foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
	{
		plugin->dataManager = new DataManagerClient(plugin);
		//DataPlugins are also moved to the network thread, is it necessary to have a dedicated thread for them ?
		plugin->moveToThread(secondaryThread);
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
		emit loadProgressChange(50 + 50 * i / _plugins.count());
    }
	_loaded = true;
	emit loadProgressChange(100);
}

bool    PluginManagerClient::loadPlugin(QString pluginName, QDir path)
{
	QTranslator *translator;
    QPluginLoader loader(path.absoluteFilePath(pluginName));
    MetaPlugin *metaPlugin = qobject_cast<MetaPlugin*>(loader.instance());
    if (! metaPlugin)
    {
		qWarning() << loader.errorString();
        return (false);
    }
	translator = new QTranslator();
	LocalSettings settings;
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
