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

public:
	UserDataBasePlugin();
private:
	UserData*				_nobody;


	//UserDataPlugin
public:
	inline UserData*		nobody() const { return _nobody; }
	UserData*				user(quint32 userId);
	UserData*				user(const QString login);
	UserData*				createUser(const QString &login);
	QList<UserData*>		parentsOfStudent(const UserData* student) const;
#ifdef HORUS_SERVER
	void					userDisconnected(UserData* user);
	UserData*				authenticatePassword(const QString& login, const QByteArray& password);
	UserData*				authenticateSession (const QString& login, const QByteArray& sesion);
#endif


	//DataPlugin
public:
	void					load();
	void					unload();
	bool					canLoad() const;
	QList<Data*>			allDatas() const;
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
	QAbstractListModel*		listModel() const;
#endif
protected:
	//! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


	//Plugin
public:
	inline const QString	pluginVersion() const { return "0.1"; }
};

#endif // USERDATABASEPLUGIN_H
