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
#ifndef PLUGINMANAGERSERVER_H
#define PLUGINMANAGERSERVER_H

#include <QHash>
#include <QList>
#include <QString>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
#include "../Common/PluginPacket.h"
#include "Sql.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManagerServer : public PluginManager
{
    Q_OBJECT
	Q_INTERFACES(PluginManagerSrv)

public:
    void load();
    const QHash<QString, Plugin*>& plugins() const;
    UserData*                      currentUser() const;
    void                           setCurrentUser(UserData* user);
	QSqlQuery					   sqlQuery();
	void						   threadFinnished();

    static PluginManagerServer* instance();

private slots:
    void sendPluginPacket(UserData* user, const PluginPacket packet);

private:
	PluginManagerServer() {}
	QHash<QString,Plugin*>		_plugins;
	QHash<Qt::HANDLE,UserData*> _users;
	QHash<Qt::HANDLE,Sql*>		_sqlConnexions;
};

#endif // PLUGINMANAGERSERVER_H
