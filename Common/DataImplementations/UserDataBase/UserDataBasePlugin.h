#ifndef USERDATABASEPLUGIN_H
#define USERDATABASEPLUGIN_H

#include <QHash>
#include "../../UserDataPlugin.h"

class Data;
class UserData;
class UserDataBase;
class UserDataBasePlugin : public UserDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerUserDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientUserDataPlugin)
#endif
	friend class UserDataBase;

private:
	QHash<quint32,UserData*>	users;

	//UserDataPlugin
public:
	UserData*				nobody();
	UserData*				user(quint32 userId);
	UserData*				user(const QString login);
	const QHash<quint32,UserData*>&	allUser();
	UserData*				createUser(const QString &login);
#ifdef HORUS_SERVER
	void					userDisconnected(UserData* user);
	UserData*				authenticatePassword(const QString& login, const QByteArray& password);
	UserData*				authenticateSession (const QString& login, const QByteArray& sesion);
#endif


	//DataPlugin
public:
	QList<Data*>			allDatas() const;
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
	//! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


	//Plugin
public:
	inline const QString	pluginVersion() const { return "0.1"; }
};

#endif // USERDATABASEPLUGIN_H
