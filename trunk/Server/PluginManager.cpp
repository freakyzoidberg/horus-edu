#include "PluginManager.h"
#include <QCoreApplication>
#include <QStringList>
#include "../Common/CommModule.h"
#include "User.h"

PluginManager* PluginManager::instance = 0;
PluginManager* PluginManager::globalInstance()
{
    if ( ! instance)
        instance = new PluginManager;
    return instance;
}

IServerPlugin*  PluginManager::getPlugin(const QByteArray& name)
{
    return map[ name ];
}

PluginManager::PluginManager() : QObject(QCoreApplication::instance())
{
    QSettings s;
    QString path = s.value("SETTINGS/PluginsBase", "./Plugins").toString();

    s.beginGroup("Plugins");
    foreach (QString key, s.childKeys())
    {
        QString file = path + "/" + s.value(key).toString();
        QPluginLoader loader(file);
        IServerPlugin *plugin = (IServerPlugin*)loader.instance();
        if (plugin)
        {
            map[ plugin->name() ] = plugin;
            plugin->server = new InterfaceServer(plugin);
            //connect(plugin, SIGNAL(destroyed()), plugin->server, SLOT(deleteLater()));
            qDebug() << "PluginManager:" << loader.fileName() << "loaded";
        }
        else
            qDebug() << "PluginManager:" << file << loader.errorString();
    }
    s.endGroup();
}
