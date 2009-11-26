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
#ifndef PLUGINMANAGERCLIENT_H
#define PLUGINMANAGERCLIENT_H

#include <QHash>
#include <QList>
#include <QString>
#include <QDir>
#include <QEvent>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
#include "../Common/PluginPacket.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  pluginManager.findPlugin("NameOfThePlugin")
 *  pluginManager.findPlugin<NetworkPlugin*>()
 *  pluginManager.findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  pluginManager.findPlugins<NetworkPlugin*>()
 */

class PluginManagerClient : public PluginManager
{
	Q_OBJECT
	Q_INTERFACES(PluginManagerCli)

public:
	//PluginManager Interface
	inline const QHash<QString, Plugin*>&	plugins() const { return _plugins; }
	inline UserData*						currentUser() const { return _currentUser; }

public:
	static PluginManagerClient*				instance();
	inline void								setCurrentUser(UserData* _user) { _currentUser = _user; }
	inline bool								isLoaded() { return _loaded; }

public slots:
	void									loadPlugins();

private slots:
	void									sendPluginPacket(const PluginPacket packet);

signals:
	void									sendPacket(const QByteArray packet);
	void									loadProgressChange(int percent);
	void									loaded();

private:
	bool									loadPlugin(QString pluginName, QDir path);

	QHash<QString,Plugin*>					_plugins;
	UserData*								_currentUser;
	bool									_loaded;

	PluginManagerClient() { _currentUser = 0; _loaded = false; }
	~PluginManagerClient() {}
};

#endif // PLUGINMANAGERCLIENT_H
