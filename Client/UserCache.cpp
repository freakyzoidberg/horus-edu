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
#include "UserCache.h"

#include <QDataStream>
#include <QFile>
#include <QDir>

#include "PluginManagerClient.h"
#include "../Common/DataPlugin.h"
#include "../Common/UserData.h"

UserCache::UserCache(const QString& login, const QDateTime lastUpdate, const QDateTime lastSessionValidity)
{
	_login = login;
	_lastUpdate = lastUpdate;
	_lastSessionValidity = lastSessionValidity;
	_loaded = false;
}

void UserCache::load()
{
	QFile file(QDir::tempPath()+"/HorusCache-"+_login);
	file.open(QIODevice::ReadOnly);
	QDataStream streamAll(&file);
	streamAll >> _lastSession;
	PluginManagerClient* pluginManager = PluginManagerClient::instance();

	QHash<QString,DataPlugin*> plugins;
	foreach (DataPlugin* plugin, pluginManager->findPlugins<DataPlugin*>())
		plugins.insert(plugin->dataType(), plugin);

	for (int progress = 100;  ! streamAll.atEnd(); progress += 100)
	{
		QString type;
		QByteArray binPlugin;
		streamAll >> type >> binPlugin;
		DataPlugin* plugin = plugins.value(type);

		if (plugin)
		{
			QDataStream streamPlugin(&binPlugin, QIODevice::ReadOnly);
			while ( ! streamPlugin.atEnd())
			{
				quint8 status;
				streamPlugin >> status;
				Data* data = plugin->dataWithKey(streamPlugin);
				data->_status = status;
				data->dataFromStream(streamPlugin);
				emit data->statusChanged();
				emit plugin->dataStatusChanged(data);
				emit data->updated();
				emit plugin->dataUpdated(data);
			}
		}
		emit loadProgressChange(progress / plugins.count());
	}

	pluginManager->setCurrentUser(pluginManager->findPlugin<UserDataPlugin*>()->user(_login));
	_loaded = true;
	emit loadProgressChange(100);
	emit loaded();
}

void UserCache::save()
{
	QFile file(QDir::tempPath()+"/HorusCache-"+_login);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream streamAll(&file);
	PluginManagerClient* plugins = PluginManagerClient::instance();
	streamAll << _lastSession;

	foreach (DataPlugin* plugin, plugins->findPlugins<DataPlugin*>())
	{
		QByteArray binPlugin;
		QDataStream streamPlugin(&binPlugin, QIODevice::WriteOnly);

		foreach (Data* data, plugin->allDatas())
			if (data->status() != Data::EMPTY && data->status() != Data::REMOVED)
			{
				streamPlugin << data->status();
				data->keyToStream(streamPlugin);
				data->dataToStream(streamPlugin);
			}

		streamAll << plugin->dataType() << binPlugin;
	}

	_lastUpdate = QDateTime::currentDateTime();
}
