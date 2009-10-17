#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QList>
#include <QObject>
#include "UserCache.h"

class CacheManager : public QObject
{
  Q_OBJECT
public:
	static CacheManager*			instance();
	UserCache*						userCache(const QString& login);
	inline UserCache*				autoLoginCache() { return _autoLogin; }
	inline const QList<UserCache*>&	availableCaches() { return _caches; }

public slots:
	void							save();

private:
									CacheManager();
									~CacheManager() {}
	QList<UserCache*>				_caches;
	UserCache*						_autoLogin;
};

#endif // CACHEMANAGER_H
