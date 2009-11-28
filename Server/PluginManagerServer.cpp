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
	Sql* conn = _sqlConnexions.value(thread);
	if ( ! conn)
	{
		conn = new Sql;
		_sqlConnexions.insert(thread, conn);
	}

	return QSqlQuery(QSqlDatabase::database(*conn));
}

void PluginManagerServer::threadFinnished()
{
	Qt::HANDLE thread = QThread::currentThreadId();
	Sql* sql = _sqlConnexions.take(thread);
	if (sql)
		delete sql;

	_users.remove(thread);
}
