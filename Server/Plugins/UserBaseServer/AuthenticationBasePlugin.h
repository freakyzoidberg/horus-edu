#ifndef AUTHENTICATIONBASEPLUGIN_H
#define AUTHENTICATIONBASEPLUGIN_H

#include "../../AuthenticationPlugin.h"
class UserDataBasePlugin;

class AuthenticationBasePlugin : public AuthenticationPlugin
{
	Q_OBJECT
	Q_INTERFACES(AuthenticationPlugin)

public:
	AuthenticationBasePlugin(UserDataBasePlugin* userDataPlugin);

	//Plugin
	inline const QString	pluginVersion() const { return "0.1"; }


	//NetworkPlugin
	void					receivePacket(UserData* user, const PluginPacket);


	//AuthenticationPlugin
	UserData*				authenticatePassword(const QString& login, const QByteArray& password);
	UserData*				authenticateSession (const QString& login, const QByteArray& sesion);
	void					userDisconnected(UserData* user);


	//! Create a random key to be able to identify a user without the password.
	QByteArray				createSession(UserData* user, const QDateTime& end);
	//! Destroy the session generated to allow only password authentication.
	void					destroySession(UserData* user);

private:
	void					updateLastLogin(UserData* user);
	UserDataBasePlugin*		_userDataPlugin;
};

#endif // AUTHENTICATIONBASEPLUGIN_H
