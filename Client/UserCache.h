/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef USERCACHE_H
#define USERCACHE_H

#include <QObject>
#include <QDateTime>
class UserData;

class UserCache : public QObject
{
	Q_OBJECT

	friend class CacheManager;
public slots:
	void						load();
	void						save();

public:
	inline bool					isLoaded()	  const { return _loaded; }

	inline const QString&		login()		  const { return _login; }
	inline const QDateTime&		lastUpdate()  const { return _lastUpdate; }
	inline void					setLastUpdate(const QDateTime& lastUpdate) { _lastUpdate = lastUpdate; }

	inline const QByteArray&	lastSession() const { return _lastSession; }
	inline const QDateTime&		lastSessionValidity() const { return _lastSessionValidity; }
	inline void					setLastSession(const QByteArray& session, const QDateTime& validity) { _lastSession = session; _lastSessionValidity = validity; }

signals:
	void						loadProgressChange(int progress);
	void						loaded();

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
