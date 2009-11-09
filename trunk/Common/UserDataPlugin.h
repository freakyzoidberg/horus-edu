#ifndef USERDATAPLUGIN_H
#define USERDATAPLUGIN_H

#include "Defines.h"

#include <QHash>
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
	virtual UserData*		nobody() = 0;
	virtual UserData*		user(quint32 userId) = 0;
	virtual UserData*		user(const QString login) = 0;
	virtual const QHash<quint32,UserData*>&	allUser() = 0;
	virtual UserData*		createUser(const QString &login) = 0;
#ifdef HORUS_SERVER
	virtual void			userDisconnected(UserData* user) = 0;
	virtual UserData*		authenticatePassword(const QString& login, const QByteArray& password) = 0;
	virtual UserData*		authenticateSession (const QString& login, const QByteArray& sesion) = 0;
#endif
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
