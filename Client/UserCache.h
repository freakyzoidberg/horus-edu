#ifndef USERCACHE_H
#define USERCACHE_H

#include <QDateTime>
class UserData;

class UserCache
{
	friend class CacheManager;
public:
	void					loadCache();
	void					saveCache();

	inline const QDateTime&	lastUpdate() const { return _lastUpdate; }
	inline const QString&	login()		 const { return _user; }
	inline bool				isLoaded()	 const { return _loaded; }

private:
	QDateTime				_lastUpdate;
	QString					_login;
	bool					_loaded;

	//present only after being loaded
	QByteArray				_lastSession;

							UserCache(const QString& login, const QDateTime lastUpdate = QDateTime());
							~UserCache() {}
};

#endif // USERCACHE_H
