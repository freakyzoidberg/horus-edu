#include "PluginManager.h"
#include <QCoreApplication>
#include "../Common/CommModule.h"

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
            map[ plugin->getName() ] = plugin;
            connect(plugin, SIGNAL(sendPacket(quint32,const ModulePacket&)), this, SLOT(moduleSendPacket(quint32,const ModulePacket&)), Qt::DirectConnection);
            qDebug() << "PluginManager:" << loader.fileName() << "loaded";
        }
        else
            qDebug() << "PluginManager:" << file << loader.errorString();
    }
    s.endGroup();
}

void PluginManager::moduleSendPacket(quint32 userId, const ModulePacket& packet)
{
    CommModule p = packet;
    User* usr = User::getUser(userId);
    if (usr)
    {
        qDebug() << "[out]" << p;
        usr->sendPacket( p.getPacket() );
    }
}
