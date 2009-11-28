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
#ifndef USERDATAPLUGIN_H
#define USERDATAPLUGIN_H

#include "Defines.h"

#include "DataPlugin.h"

class UserData;
class UserDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

	//Plugin
public:
	inline const QString	pluginName() const { return "User Data Plugin"; }
	inline const QString	dataType() const { return "User"; }


	//UserDataPlugin
public:
	virtual UserData*		nobody() const = 0;
	virtual UserData*		user(quint32 userId) = 0;
	virtual UserData*		user(const QString login) = 0;
	virtual UserData*		createUser(const QString &login) = 0;
	virtual QList<UserData*> parentsOfStudent(const UserData* student) const = 0;
};


#ifdef HORUS_SERVER
typedef UserDataPlugin ServerUserDataPlugin;
Q_DECLARE_INTERFACE(ServerUserDataPlugin, "net.horus.ServerUserDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef UserDataPlugin ClientUserDataPlugin;
Q_DECLARE_INTERFACE(ClientUserDataPlugin, "net.horus.ClientUserDataPlugin/1.0");
#endif

#endif // USERDATAPLUGIN_H
