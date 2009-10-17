#ifndef USERCACHE_H
#define USERCACHE_H

#include <QDateTime>
class UserData;

class UserCache
{
	friend class CacheManager;
public:
	void						load();
	inline bool					isLoaded()	  const { return _loaded; }
	void						save();

	inline const QString&		login()		  const { return _login; }
	inline const QDateTime&		lastUpdate()  const { return _lastUpdate; }
	inline const QByteArray&	lastSession() const { return _lastSession; }

private:
	QDateTime					_lastUpdate;
	QString						_login;
	bool						_loaded;

	//present only after being loaded
	QByteArray					_lastSession;

								UserCache(const QString& login, const QDateTime lastUpdate = QDateTime());
								~UserCache() {}
};

#endif // USERCACHE_H
