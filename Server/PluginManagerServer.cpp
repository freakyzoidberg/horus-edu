#include "PluginManagerServer.h"
#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/MetaPlugin.h"
#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

QHash<QString,Plugin*> PluginManagerServer::_plugins;
const QHash<QString, Plugin*>& PluginManagerServer::plugins() const { return _plugins; }

PluginManagerServer::PluginManagerServer() { }

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
            {
                _plugins.insert(plugin->pluginName(), plugin);
                qDebug() << "PluginManager:" << plugin->pluginName() << "loaded from" << loader.fileName();
            }
        else
            qDebug() << "PluginManager:" << loader.errorString();
    }
    s.endGroup();

    DataPlugin* p;
    foreach (Plugin* plugin, plugins())
    {
        plugin->pluginManager = PluginManagerServer::instance();
        if ((p = qobject_cast<DataPlugin*>(plugin)))
            p->dataManager = new DataManagerServer(p);
    }
}
