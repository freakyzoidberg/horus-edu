#include "PluginManagerServer.h"
#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/MetaPlugin.h"
#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include <QThread>

const QHash<QString, Plugin*>& PluginManagerServer::plugins() const { return _plugins; }

PluginManagerServer::PluginManagerServer() { }

UserData* PluginManagerServer::currentUser() const { return users[ QThread::currentThreadId() ]; }

void PluginManagerServer::setCurrentUser(UserData* user) { users[ QThread::currentThreadId() ] = user; }

PluginManagerServer* PluginManagerServer::instance()
{
    static PluginManagerServer pmi;
    return &pmi;
}

void PluginManagerServer::load()
{
    QSettings s;
    QString path = s.value("SETTINGS/PluginsBase", "./Plugins").toString();

    s.beginGroup("Plugins");
    foreach (QString key, s.childKeys())
    {
        QString file = path + "/" + s.value(key).toString();
        QPluginLoader loader(file);
        MetaPlugin *metaPlugin = (MetaPlugin*)loader.instance();
        if (metaPlugin)
            foreach (Plugin* plugin, metaPlugin->pluginList)
                _plugins.insert(plugin->pluginName(), plugin);
        else
            qDebug() << "PluginManager:" << loader.errorString();
    }
    s.endGroup();

    // every Plugins
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
    }

    // DataPlugin
    foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
        plugin->dataManager = new DataManagerServer(plugin);
}
