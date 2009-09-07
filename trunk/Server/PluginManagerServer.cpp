#include "PluginManagerServer.h"
#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/Plugin.h"
#include "../Common/MetaPlugin.h"
#include "ClientSocket.h"
#include "../Common/CommPlugin.h"
#include "NetworkPlugin.h"
#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>
#include <QThread>
#include <QtSql>
#include "Sql.h"

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
    Sql db;
    QSqlQuery query(QSqlDatabase::database(db));
    foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
    {
        plugin->dataManager = new DataManagerServer(plugin);
        plugin->loadDataBase(query);
    }

    // NetworkPlugin
    foreach (NetworkPlugin* plugin, findPlugins<NetworkPlugin*>())
        connect(plugin, SIGNAL(sendPacket(UserData*,PluginPacket)), this, SLOT(sendPluginPacket(UserData*,PluginPacket)));
    qRegisterMetaType<PluginPacket>("PluginPacket");
}

void PluginManagerServer::sendPluginPacket(UserData* user, const PluginPacket packet)
{
    ClientSocket* socket = ClientSocket::connectedUsers.value( user );
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, CommPlugin(packet).getPacket()));
    else
        qDebug() << "PluginManagerServer::sendPluginPacket error user not connected";
}
