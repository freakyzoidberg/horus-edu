#include "UserCache.h"

#include <QDataStream>
#include <QFile>
#include <QDir>

#include "MetaManager.h"
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
	PluginManager* plugins = MetaManager::getInstance()->findManager<PluginManager*>();
	streamAll >> _lastSession;

	while ( ! streamAll.atEnd())
	{
		QString type;
		QByteArray binPlugin;
		streamAll >> type >> binPlugin;

		DataPlugin* plugin = plugins->findPlugin<DataPlugin*>(type);
		if (plugin)
		{
			QDataStream streamPlugin(&binPlugin, QIODevice::ReadOnly);
			while ( ! streamPlugin.atEnd())
			{
				quint8 status;
				streamPlugin >> status;
				Data* data = plugin->getDataWithKey(streamPlugin);
				data->dataFromStream(streamPlugin);
				data->_status = Data::CACHED;
				if (status != Data::UPTODATE)
					data->setStatus(status);
			}
		}
	}

	((PluginManagerClient*)(plugins))->setCurrentUser(plugins->findPlugin<UserDataPlugin*>()->getUser(_login));
	_loaded = true;
}

void UserCache::save()
{
	QFile file(QDir::tempPath()+"/HorusCache-"+_login);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream streamAll(&file);
	PluginManager* plugins = MetaManager::getInstance()->findManager<PluginManager*>();
	streamAll << _lastSession;

	foreach (DataPlugin* plugin, plugins->findPlugins<DataPlugin*>())
	{
		QByteArray binPlugin;
		QDataStream streamPlugin(&binPlugin, QIODevice::WriteOnly);

		foreach (Data* data, plugin->allDatas())
		{
			streamPlugin << data->status();
			data->keyToStream(streamPlugin);
			data->dataToStream(streamPlugin);
		}

		streamAll << plugin->getDataType() << binPlugin;
	}

	_lastUpdate = QDateTime::currentDateTime();
}
