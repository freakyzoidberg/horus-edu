#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QList>
#include "UserCache.h"

class CacheManager
{
public:
	static CacheManager*		instance();
	UserCache*					userCache(UserData* user);
	const QList<UserCache*>&	availableCaches() { return _caches; }
	void						saveCache();

private:
								CacheManager();
								~CacheManager() {}
	QList<UserCache*>			_caches;
};

#endif // CACHEMANAGER_H
