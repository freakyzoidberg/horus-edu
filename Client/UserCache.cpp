#include "UserCache.h"

#include <QDataStream>
#include <QFile>
#include <QDir>

#include "MetaManager.h"
#include "../Common/PluginManager.h"
#include "../Common/DataPlugin.h"
#include "../Common/UserData.h"

UserCache::UserCache(const QString& login, const QDateTime lastUpdate)
{
	_login = login;
	_lastUpdate = lastUpdate;
	_loaded = false;
}

void UserCache::load()
{
	QFile file(QDir::tempPath()+"/HorusCache-"+_login);
	file.open(QIODevice::ReadOnly);
	QDataStream stream(&file);
	PluginManager* plugins = MetaManager::getInstance()->findManager<PluginManager*>();
	stream >> _lastSession >> _lastSessionValidity;

	while ( ! stream.atEnd())
	{
		QString type;
		quint32 nbrData;
		stream >> type >> nbrData;
		DataPlugin* plugin = plugins->findPlugin<DataPlugin*>(type);
		if (plugin)
			for (quint32 i; i < nbrData; i++)
			{
				Data* data = plugin->getDataWithKey(stream);
				data->dataFromStream(stream);
				data->_status = Data::CACHED;
			}
	}

	_loaded = true;
}

void UserCache::save()
{
	QFile file(QDir::tempPath()+"/HorusCache-"+_login);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream stream(&file);
	PluginManager* plugins = MetaManager::getInstance()->findManager<PluginManager*>();
	stream << _lastSession << _lastSessionValidity;

	foreach (DataPlugin* plugin, plugins->findPlugins<DataPlugin*>())
	{
		QList<Data*> datas = plugin->allDatas();
		stream << plugin->getDataType() << (quint32)datas.size();
		foreach (Data* data, datas)
		{
			data->keyToStream(stream);
			data->dataToStream(stream);
		}
	}

	_lastUpdate = QDateTime::currentDateTime();
}
