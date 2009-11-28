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
#ifndef AUTHENTICATIONPLUGIN_H
#define AUTHENTICATIONPLUGIN_H

#include "NetworkPlugin.h"
class UserData;

class AuthenticationPlugin : public NetworkPlugin
{
	Q_OBJECT
	Q_INTERFACES(NetworkPluginServer)

	//Plugin
public:
	inline const QString	pluginName() const { return "AuthenticationPlugin"; }


	virtual UserData*		authenticatePassword(const QString& login, const QByteArray& password) = 0;
	virtual UserData*		authenticateSession (const QString& login, const QByteArray& sesion) = 0;
	virtual void			userDisconnected(UserData* user) = 0;

	//! Create a random key to be able to identify a user without the password.
	virtual QByteArray		createSession(UserData* user, const QDateTime& end) = 0;
	//! Destroy the session generated to allow only password authentication.
	virtual void			destroySession(UserData* user) = 0;
};

Q_DECLARE_INTERFACE(AuthenticationPlugin, "net.horus.AuthenticationPlugin/1.0");

#endif // AUTHENTICATIONPLUGIN_H
