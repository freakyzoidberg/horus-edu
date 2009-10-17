#include "CacheManager.h"
#include "MetaManager.h"
#include "PluginManagerClient.h"

CacheManager* CacheManager::instance()
{
	static CacheManager* cache = new CacheManager;
	return cache;
}

CacheManager::CacheManager()
{
	_autoLogin = 0;

	QFile file("/tmp/HorusCache");
	file.open(QIODevice::ReadOnly);
	QDataStream stream(&file);

	QString autoLogin;
	stream >> autoLogin;

	//	foreach (UserCache* cache, _caches)
	while ( ! file.atEnd())
	{
		QString login;
		QDateTime lastLogin;
		stream >> login >> lastLogin;
		UserCache* cache = new UserCache(login, lastLogin);
		_caches.append(cache);
		if (login == autoLogin)
			_autoLogin = cache;
	}
}

UserCache* CacheManager::userCache(const QString& login)
{
	foreach (UserCache* cache, _caches)
		if (cache->login() == login)
			return cache;

	UserCache* userCache = new UserCache(login);
	_caches.append(userCache);
	return userCache;
}

void CacheManager::save()
{
	QFile file("/tmp/HorusCache");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream stream(&file);
	UserData* currentUser = MetaManager::getInstance()->findManager<PluginManager*>()->currentUser();

	if (_autoLogin)
		stream << _autoLogin->login();
	else
		stream << QString();

	foreach (UserCache* cache, _caches)
	{
		stream << cache->login() << cache->lastUpdate();

		if (cache->login() == currentUser->login())
			cache->save();
	}
}
