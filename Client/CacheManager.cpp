#include "CacheManager.h"
#include "PluginManagerClient.h"
#include "SecondaryThread.h"

CacheManager* CacheManager::instance()
{
	static CacheManager* cache = 0;
	if ( ! cache)
	{
		cache = new CacheManager;
		cache->moveToThread(SecondaryThread::instance());
	}
	return cache;
}

CacheManager::CacheManager()
{
	_autoLogin = 0;

	QFile file(QDir::tempPath()+"/HorusCache");
	file.open(QIODevice::ReadOnly);
	QDataStream stream(&file);

	QString autoLogin;
	stream >> autoLogin;

	while ( ! file.atEnd())
	{
		QString login;
		QDateTime lastLogin;
		QDateTime lastSessionValidity;
		stream >> login >> lastLogin >> lastSessionValidity;
		UserCache* cache = new UserCache(login, lastLogin, lastSessionValidity);
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
	QFile file(QDir::tempPath()+"/HorusCache");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream stream(&file);
	UserData* currentUser = PluginManagerClient::instance()->currentUser();

	if (_autoLogin)
		stream << _autoLogin->login();
	else
		stream << QString();

	foreach (UserCache* cache, _caches)
	{
		stream << cache->login() << cache->lastUpdate() << cache->lastSessionValidity();

		if (currentUser && cache->login() == currentUser->login())
			cache->save();
	}
}
