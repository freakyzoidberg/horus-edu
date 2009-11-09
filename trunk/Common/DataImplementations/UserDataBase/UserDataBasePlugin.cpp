#include "UserDataBasePlugin.h"
#include "UserDataBase.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

UserData* UserDataBasePlugin::nobody()
{
	return user(0);
}

UserData* UserDataBasePlugin::user(quint32 userId)
{
    if ( ! users.contains(userId))
	{
		UserData* user = new UserDataBase(userId, this);
		user->moveToThread(this->thread());
//		connect(user, SIGNAL(destroyed()), this,
		users.insert(userId, user);
	}
    return users[userId];
}

UserData* UserDataBasePlugin::user(const QString login)
{
	foreach (UserData* u, users)
		if (u->login() == login)
			return u;
	return 0;
}

const QHash<quint32, UserData*>&     UserDataBasePlugin::allUser()
{
    return users;
}

Data* UserDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return user(tmpId);
}

UserData* UserDataBasePlugin::createUser(const QString &login)
{
	static quint32 tmpId = 0;
	tmpId--;

	UserDataBase* u = ((UserDataBase*)( user(tmpId)) );
	u->_login = login;
	u->setName("New user");
	u->setSurname("New user");
    return u;
}

QList<Data*> UserDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, users)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}

#ifdef HORUS_CLIENT
void UserDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	UserDataBase* user = ((UserDataBase*)(d));
	users.remove(user->_id);
	s >> user->_id;
	users.insert(user->_id, user);
	qDebug() << "User data Have a New Key" << user->_id;
}
#endif
#ifdef HORUS_SERVER
void UserDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id,login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users;");
    query.exec();
    while (query.next())
    {
		UserDataBase* u = (UserDataBase*)(user(query.value(0).toUInt()));
		u->_login       = query.value(1).toString();
		u->_level       = (UserLevel)(query.value(2).toUInt());
		u->_lastLogin   = query.value(3).toDateTime();
		u->_surname     = query.value(4).toString();
		u->_name        = query.value(5).toString();
		u->_birthDate   = query.value(6).toDate();
		u->_picture     = query.value(7).toByteArray();
		u->_address     = query.value(8).toString();
		u->_phone       = query.value(9).toString();
		u->_country     = query.value(10).toString();
		u->_language    = query.value(11).toString();
		u->_node        = pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(12).toUInt() );
		u->_enabled     = query.value(13).toBool();
		u->_lastChange  = query.value(14).toDateTime();
		u->_status      = Data::UPTODATE;
	}
}

QList<Data*> UserDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (UserData* data, users)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}

void UserDataBasePlugin::userDisconnected(UserData*)
{
}

UserData* UserDataBasePlugin::authenticatePassword(const QString& login, const QByteArray& password)
{
	if (login.length() > 32 || password.length() != SHA1_WORD_SIZE)
    {
        qDebug() << "UserDataBasePlugin::authenticatePassword Password is not a SHA1 hash.";
        return 0;
    }

	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND password=?;");
    query.addBindValue(login);
    query.addBindValue(password.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataBasePlugin::authenticatePassword pair user/password not found in enabled users.";
        return 0;
    }

	UserDataBase* u = (UserDataBase*)(user(query.value(0).toUInt()));
	u->updateLastLogin();
	return u;
}

UserData* UserDataBasePlugin::authenticateSession(const QString& login, const QByteArray& session)
{
	if (login.length() > 32 || session.length() != SESSION_WORD_SIZE)
    {
        qDebug() << "UserDataBasePlugin::authenticateSession Session key have an invalid size.";
        return 0;
    }

	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND session_key=?;");
    query.addBindValue(login);
    query.addBindValue(session.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataBasePlugin::authenticateSession pair user/session not found in enabled users.";
        return 0;
    }

	UserDataBase* u = (UserDataBase*)(user(query.value(0).toUInt()));
	u->updateLastLogin();
	return u;
}
#endif
