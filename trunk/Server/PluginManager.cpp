#include "../Common/PluginManager.h"
#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

#include "../Common/MetaPlugin.h"

QHash<QString,Plugin*> PluginManager::plugins;

void PluginManager::load()
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
                plugins[ plugin->pluginName() ] = plugin;
                qDebug() << "PluginManager:" << plugin->pluginName() << "loaded from" << loader.fileName();
            }
        else
            qDebug() << "PluginManager:" << loader.errorString();
    }
    s.endGroup();
}
