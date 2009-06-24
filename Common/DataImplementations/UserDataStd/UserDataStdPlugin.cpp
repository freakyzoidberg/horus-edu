#include "UserDataStdPlugin.h"
#include "UserDataStd.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

UserData* UserDataStdPlugin::getUser(quint32 userId)
{
    if ( ! users.contains(userId))
    {
        UserDataStd* user = new UserDataStd(userId, this);
        users[userId] = user;
    }
    qDebug() << PluginManager().findPlugins<Plugin*>();
    return users[userId];
}

Data* UserDataStdPlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getUser(tmpId);
}

#ifdef HORUS_CLIENT
void UserDataStdPlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((UserDataStd*)(d))->id = tmpId;
}
#endif
#ifdef HORUS_SERVER
bool UserDataStdPlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}

void UserDataStdPlugin::userDisconnected(UserData* TODO)
{
}

UserData* UserDataStdPlugin::authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password)
{
    if (login.length() > 32 || password.length() != SHA1_WORD_SIZE)
    {
        qDebug() << "UserDataStdPlugin::authenticatePassword Password is not a SHA1 hash.";
        return 0;
    }

    query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND password=?;");
    query.addBindValue(login);
    query.addBindValue(password.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataStdPlugin::authenticatePassword pair user/password not found in enabled users.";
        return 0;
    }

    UserData* user = getUser(query.value(0).toUInt());
    user->fillFromDatabase(query);
    user->setStatus(user, Data::UPTODATE);
    user->newSession(query);
    return user;
}

UserData* UserDataStdPlugin::authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& session)
{
    if (login.length() > 32 || session.length() != SESSION_WORD_SIZE)
    {
        qDebug() << "UserDataStdPlugin::authenticateSession Session key have an invalid size.";
        return 0;
    }

    query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND session_key=?;");
    query.addBindValue(login);
    query.addBindValue(session.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataStdPlugin::authenticateSession pair user/session not found in enabled users.";
        return 0;
    }

    UserData* user = getUser(query.value(0).toUInt());
    user->fillFromDatabase(query);
    user->setStatus(user, Data::UPTODATE);
    user->newSession(query);
    return user;
}
#endif
