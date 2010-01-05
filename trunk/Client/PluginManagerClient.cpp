/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "PluginManagerClient.h"

#include <../Common/LocalSettings.h>
#include <QApplication>
#include <QPluginLoader>
#include <QTranslator>
#include <QDebug>
#include "MainFrame/MainFrame.h"

#include "../Common/MetaPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/TreeData.h"
#include "../Common/UserData.h"
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
//		_instance->moveToThread(SecondaryThread::instance());
		_instance->moveToThread(QCoreApplication::instance()->thread());
	}
	return _instance;
}

PluginManagerClient::PluginManagerClient()
{
	_currentUser = 0;
	_rootNode = 0;
	_nobody = 0;
	_loaded = false;
}

void PluginManagerClient::reloadPlugins()
{
	_loaded = false;
	emit loadProgressChange(0);
	int total = _plugins.count();
	int pos = 0;
	foreach (Plugin* plugin, _plugins)
	{
		plugin->unload();
		emit loadProgressChange(++pos * 50 / total);
	}
	foreach (Plugin* plugin, _plugins)
	{
		plugin->load();
		emit loadProgressChange(++pos * 50 / total + 50);
	}
	_loaded = true;
	emit loadProgressChange(100);
	emit loaded();
}

void PluginManagerClient::loadPlugins()
{
	if (_loaded)
		return reloadPlugins();

	_currentUser = 0;
	LocalSettings settings;
	QStringList	pluginsToLoad;
	QStringList	pluginFilter;

	MainFrame* main = new MainFrame;
	_plugins.insert(main->pluginName(), main);

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
# define PLUGIN_FILTER  "*.dylib"
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
		//DataPlugins are also moved to the network thread, is it necessary to have a dedicated thread for them ?
		plugin->moveToThread(secondaryThread);
		plugin->dataManager = new DataManagerClient(plugin);
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
		if (_plugins.count())
			emit loadProgressChange(50 + 50 * i / _plugins.count());
    }
	if ( ! findPlugin<UserDataPlugin*>() || ! findPlugin<TreeDataPlugin*>())
		qFatal(tr("Horus Client cannot launch. You need at least a User Data Plugin and a Tree Data Plugin").toAscii().data());


	_rootNode = findPlugin<TreeDataPlugin*>()->rootNode();
	_nobody = findPlugin<UserDataPlugin*>()->nobody();
	_loaded = true;
	emit loadProgressChange(100);
	emit loaded();
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
