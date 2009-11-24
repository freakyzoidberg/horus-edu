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
#include "Sql.h"

const QHash<QString, Plugin*>& PluginManagerServer::plugins() const { return _plugins; }

UserData* PluginManagerServer::currentUser() const { return _users[ QThread::currentThreadId() ]; }

void PluginManagerServer::setCurrentUser(UserData* user) { _users[ QThread::currentThreadId() ] = user; }

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

	// DataPlugin
	foreach (DataPlugin* plugin, findPlugins<DataPlugin*>())
		plugin->dataManager = new DataManagerServer(plugin);

	// every Plugins
	foreach (Plugin* plugin, _plugins)
		plugin->pluginManager = this;

	// every Plugins
    foreach (Plugin* plugin, _plugins)
        if ( ! plugin->canLoad())
        {
            _plugins.remove(plugin->pluginName());
            delete plugin;
        }
        else
            plugin->load();

    // NetworkPlugin
    qRegisterMetaType<PluginPacket>("PluginPacket");
    qRegisterMetaType<UserData*>("UserData*");
    foreach (NetworkPlugin* plugin, findPlugins<NetworkPlugin*>())
        connect(plugin, SIGNAL(sendPacket(UserData*,PluginPacket)), this, SLOT(sendPluginPacket(UserData*,PluginPacket)));
}

void PluginManagerServer::sendPluginPacket(UserData* user, const PluginPacket packet)
{
    ClientSocket* socket = ClientSocket::connectedUsers.value( user );
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, CommPlugin(packet).getPacket()));
    else
        qDebug() << "PluginManagerServer::sendPluginPacket error user not connected";
}

QSqlQuery PluginManagerServer::sqlQuery()
{
	Qt::HANDLE thread = QThread::currentThreadId();
	Sql* conn;

	if ( ! _sqlConnexions.contains(thread))
	{
		conn = new Sql;
		_sqlConnexions.insert(thread, conn);
	}
	else
		conn = _sqlConnexions.value(thread);

	return QSqlQuery(QSqlDatabase::database(*conn));
}

void PluginManagerServer::threadFinnished()
{
	Qt::HANDLE thread = QThread::currentThreadId();
	if (_sqlConnexions.contains(thread))
	{
		delete _sqlConnexions.value(thread);
		_sqlConnexions.remove(thread);
	}
	if (_users.contains(thread))
		_users.remove(thread);
}
