#include "AuthenticationBasePlugin.h"
#include "../../../Common/DataImplementations/UserDataBase/UserDataBase.h"
#include <QtSql>


AuthenticationBasePlugin::AuthenticationBasePlugin(UserDataBasePlugin* userDataPlugin)
{
	_userDataPlugin = userDataPlugin;
}

UserData* AuthenticationBasePlugin::authenticatePassword(const QString& login, const QByteArray& password)
{
	if (login.length() > 32 || password.length() != SHA1_WORD_SIZE)
	{
		qDebug() << "AuthenticationBasePlugin::authenticatePassword Password is not a SHA1 hash.";
		return 0;
	}

	QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
	query.prepare("SELECT`id`FROM`user`WHERE`enabled`=1 AND`login`=? AND`password`=?;");
	query.addBindValue(login);
	query.addBindValue(password.toHex());
	if ( ! query.exec() || ! query.next())
	{
		qDebug() << "AuthenticationBasePlugin::authenticatePassword pair user/password not found in enabled users.";
		return 0;
	}

	UserData* u = _userDataPlugin->user(query.value(0).toUInt());
	updateLastLogin(u);
	return u;
}

UserData* AuthenticationBasePlugin::authenticateSession(const QString& login, const QByteArray& session)
{
	if (login.length() > 32 || session.length() != SESSION_WORD_SIZE)
	{
		qDebug() << "AuthenticationBasePlugin::authenticateSession Session key have an invalid size.";
		return 0;
	}

	QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
	query.prepare("SELECT`id`FROM`user`WHERE`enabled`=1 AND`login`=? AND`session_key`=?;");
	query.addBindValue(login);
	query.addBindValue(session.toHex());
	if ( ! query.exec() || ! query.next())
	{
		qDebug() << "AuthenticationBasePlugin::authenticateSession pair user/session not found in enabled users.";
		return 0;
	}

	UserData* u = _userDataPlugin->user(query.value(0).toUInt());
	updateLastLogin(u);
	return u;
}

void AuthenticationBasePlugin::userDisconnected(UserData*)
{
}

QByteArray AuthenticationBasePlugin::createSession(UserData* user, const QDateTime& end)
{
	QByteArray session;
	for (int i = 0; i < SESSION_WORD_SIZE; i++)
		session[i] = qrand();

	QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`session_key`=?,`session_end`=? WHERE`id`=?;");
	query.addBindValue(session.toHex());
	query.addBindValue(end);
	query.addBindValue(user->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return QByteArray();
	}
	if ( ! query.numRowsAffected())
		return QByteArray();

	return session;
}

void AuthenticationBasePlugin::destroySession(UserData* user)
{
	QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`session_key`='',`session_end`=''WHERE`id`=?;");
	query.addBindValue(user->id());

	if ( ! query.exec())
		qDebug() << query.lastError();
}

void AuthenticationBasePlugin::updateLastLogin(UserData* user)
{
	QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`last_login`=? WHERE`id`=?;");
	query.addBindValue(QDateTime::currentDateTime());
	query.addBindValue(user->id());

	if ( ! query.exec())
		qDebug() << query.lastError();
}

void AuthenticationBasePlugin::receivePacket(UserData* user, const PluginPacket packet)
{
	QVariantHash hash = packet.data.toHash();

	if (packet.request == "changePassword")
	{
		QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
		query.prepare("UPDATE`user`SET`password`=? WHERE`id`=? AND`password`=?;");
		query.addBindValue(hash["newPassword"].toByteArray().toHex());
		query.addBindValue(user->id());
		query.addBindValue(hash["oldPassword"].toByteArray().toHex());
		if ( ! query.exec() || ! query.numRowsAffected())
		{
			qDebug() << query.lastError();
			hash["message"] = "Password not changed.";
			emit sendPacket(user, PluginPacket(packet.sourcePlugin, "changePasswordFail", hash));
			return;
		}
		hash["message"] = "Password succefully changed.";
		emit sendPacket(user, PluginPacket(packet.sourcePlugin, "changePasswordSuccess", hash));
		return;
	}

	if (packet.request == "resetPassword")
	{
		if (user->level() > LEVEL_ADMINISTRATOR)
		{
			hash["message"] = "Permition denied. You must be root or administrator.";
			emit sendPacket(user, PluginPacket(packet.sourcePlugin, "resetPasswordFail", hash));
			return;
		}

		QSqlQuery query = _userDataPlugin->pluginManager->sqlQuery();
		query.prepare("UPDATE`user`SET`password`=? WHERE`id`=?;");
		query.addBindValue(hash["newPassword"].toByteArray().toHex());
		query.addBindValue(hash["userId"].toUInt());
		query.addBindValue(hash["oldPassword"].toByteArray().toHex());
		if ( ! query.exec() || ! query.numRowsAffected())
		{
			qDebug() << query.lastError();
			hash["message"] = "Password not changed.";
			emit sendPacket(user, PluginPacket(packet.sourcePlugin, "resetPasswordFail", hash));
			return;
		}
		hash["message"] = "Password succefully changed.";
		emit sendPacket(user, PluginPacket(packet.sourcePlugin, "resetPasswordSuccess", hash));
		return;
	}
}
