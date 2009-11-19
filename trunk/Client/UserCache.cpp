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

		if (plugins.contains(type))
		{
			QDataStream streamPlugin(&binPlugin, QIODevice::ReadOnly);
			while ( ! streamPlugin.atEnd())
			{
				quint8 status;
				streamPlugin >> status;
				Data* data = plugins.value(type)->dataWithKey(streamPlugin);
				data->_status = Data::CACHED;
				data->dataFromStream(streamPlugin);
				if (status != Data::UPTODATE && data->status() != Data::CACHED)
					data->setStatus(status);
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
			if (data->status() != Data::EMPTY && data->status() != Data::DELETED)
			{
				streamPlugin << data->status();
				data->keyToStream(streamPlugin);
				data->dataToStream(streamPlugin);
			}

		streamAll << plugin->dataType() << binPlugin;
	}

	_lastUpdate = QDateTime::currentDateTime();
}
