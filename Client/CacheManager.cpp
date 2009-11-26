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
