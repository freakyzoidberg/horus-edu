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
	QFile file("/tmp/HorusCache");
	file.open(QIODevice::ReadOnly);
	foreach (UserCache* cache, _caches)
	{

	}
}

UserCache* CacheManager::userCache(const QString& login)
{
	foreach (UserCache* cache, _caches)
		if (cache->login() == login)
			return cache;

	UserCache* userCache = new UserCache(user);
	_caches.append(userCache);
	return userCache;
}

void CacheManager::saveCache()
{
	UserData* currentUser = MetaManager::getInstance()->findManager<PluginManager*>()->currentUser();
	foreach (UserCache* cache, _caches)
		if (cache->user() == currentUser)
			return cache->saveCache();
	qDebug() << "The cache for the current user cannot being saved.";
}
