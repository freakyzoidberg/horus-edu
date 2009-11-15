#include "UserDataBasePlugin.h"
#include "UserDataBase.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

UserDataBasePlugin::UserDataBasePlugin()
{
	_nobody = 0;
}

UserData* UserDataBasePlugin::nobody()
{
	if ( ! _nobody)
	{
		_nobody = new UserDataBase(0, this);
		_nobody->_student = _nobody;
		_nobody->_level = __LAST_LEVEL__;
		_nobody->_name = tr("Nobody");
		_nobody->_surname = tr("Nobody");
		_nobody->_login = tr("Nobody");
	}
	return _nobody;
}

UserData* UserDataBasePlugin::user(quint32 userId)
{
	if (userId == 0)
		return nobody();

	if ( ! _users.contains(userId))
	{
		UserDataBase* user = new UserDataBase(userId, this);
		user->_student = nobody();
		user->moveToThread(this->thread());
		_users.insert(userId, user);
	}
	return _users[userId];
}

UserData* UserDataBasePlugin::user(const QString login)
{
	foreach (UserData* u, _users)
		if (u->login() == login)
			return u;
	return 0;
}

const QHash<quint32, UserData*>&     UserDataBasePlugin::allUser()
{
	return _users;
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
	foreach (Data* data, _users)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}

#ifdef HORUS_CLIENT
void UserDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	UserDataBase* user = ((UserDataBase*)(d));
	_users.remove(user->_id);
	s >> user->_id;
	_users.insert(user->_id, user);
	qDebug() << "User data Have a New Key" << user->_id;
}
#endif
#ifdef HORUS_SERVER
void UserDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT enabled,login,level,password,student_class,last_login,language,surname,name,birth_date,picture,address,phone1,phone2,phone3,country,gender,occupation,pro_category,relationship,student,mtime,id FROM user;");

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	while (query.next())
	{
		UserDataBase* u = (UserDataBase*)(user(query.value(22).toUInt()));

		u->_enabled    = query.value(0).toBool();
		u->_login      = query.value(1).toString();
		u->_level      = (UserLevel)(query.value(2).toUInt());
		u->_password   = QByteArray::fromHex(query.value(3).toByteArray());
		u->_studentClass = pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(4).toUInt() );
		u->_lastLogin  = query.value(5).toDateTime();
		u->_language   = query.value(6).toString();
		u->_surname    = query.value(7).toString();
		u->_name       = query.value(8).toString();
		u->_birthDate  = query.value(9).toDate();
		u->_picture    = query.value(10).toByteArray();
		u->_address    = query.value(11).toString();
		u->_phone1     = query.value(12).toString();
		u->_phone2     = query.value(13).toString();
		u->_phone3     = query.value(14).toString();
		u->_country    = query.value(15).toString();
		u->_gender     = (UserGender)(query.value(16).toUInt());
		u->_occupation = query.value(17).toString();
		u->_proCategory  = query.value(18).toString();
		u->_relationship = query.value(19).toString();
		u->_student    = pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(20).toUInt() );
		u->_lastChange = query.value(21).toDateTime();

		disconnect(this, SLOT(nodeRemoved()));
		connect(u->_studentClass, SIGNAL(removed()), u, SLOT(nodeRemoved()));
		u->_lastChange	= query.value(14).toDateTime();
	}
}

QList<Data*> UserDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (UserData* data, _users)
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
	query.prepare("SELECT id FROM user WHERE enabled=1 AND login=? AND password=?;");
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
	query.prepare("SELECT id FROM user WHERE enabled=1 AND login=? AND session_key=?;");
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
