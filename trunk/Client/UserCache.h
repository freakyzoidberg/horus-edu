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
	inline void					setLastUpdate(const QDateTime& lastUpdate) { _lastUpdate = lastUpdate; }

	inline const QByteArray&	lastSession() const { return _lastSession; }
	inline const QDateTime&		lastSessionValidity() const { return _lastSessionValidity; }
	inline void					setLastSession(const QByteArray& session, const QDateTime& validity) { _lastSession = session; _lastSessionValidity = validity; }

private:
	QDateTime					_lastUpdate;
	QDateTime					_lastSessionValidity;
	QString						_login;
	bool						_loaded;

	//present only after being loaded
	QByteArray					_lastSession;

								UserCache(const QString& login, const QDateTime lastUpdate = QDateTime(), const QDateTime lastSessionValidity = QDateTime());
								~UserCache() {}
};

#endif // USERCACHE_H
