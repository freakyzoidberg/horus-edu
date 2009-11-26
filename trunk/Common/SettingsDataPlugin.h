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
#ifndef SETTINGSDATAPLUGIN_H
#define SETTINGSDATAPLUGIN_H

#include "DataPlugin.h"

// There is 2 params in a scope.
// If the setting is a value for the user or the system value
#define USER_SCOPE 0
#define SYSTEM_SCOPE 1
// If the setting is on the client or on the server side
#define CLIENT_SCOPE 0
#define SERVER_SCOPE 2

// So, use these values combining the 2 params
#define  CLIENT_USER_SCOPE  (CLIENT_SCOPE |  USER_SCOPE ) // = 00 = 0
#define  SERVER_USER_SCOPE  (SERVER_SCOPE |  USER_SCOPE ) // = 01 = 1
#define CLIENT_SYSTEM_SCOPE (CLIENT_SCOPE | SYSTEM_SCOPE) // = 10 = 2
#define SERVER_SYSTEM_SCOPE (SERVER_SCOPE | SYSTEM_SCOPE) // = 11 = 3

// And for a clean and optimised code, please use theses macro.
#define IS_CLIENT_SCOPE(scope)  ((scope & CLIENT_SCOPE) == CLIENT_SCOPE)
#define IS_SERVER_SCOPE(scope)  ((scope & SERVER_SCOPE) == SERVER_SCOPE)
#define IS_SYSTEM_SCOPE(scope)  ((scope & SYSTEM_SCOPE) == SYSTEM_SCOPE)
#define IS_USER_SCOPE(scope)    ((scope &  USER_SCOPE ) ==  USER_SCOPE )

class Data;
class UserData;
class SettingsData;
class SettingsDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
	inline const QString dataType() const { return "Settings"; }

  virtual SettingsData* settings(QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, UserData* user = 0) = 0;
};

#ifdef HORUS_SERVER
typedef SettingsDataPlugin ServerSettingsDataPlugin;
Q_DECLARE_INTERFACE(ServerSettingsDataPlugin, "net.horus.ServerSettingsDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef SettingsDataPlugin ClientSettingsDataPlugin;
Q_DECLARE_INTERFACE(ClientSettingsDataPlugin, "net.horus.ClientSettingsDataPlugin/1.0");
#endif

#endif // SETTINGSDATAPLUGIN_H
