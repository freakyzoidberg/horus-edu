#include "UserDataBasePlugin.h"
#include "UserDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

UserDataBasePlugin::UserDataBasePlugin()
{
#ifdef HORUS_CLIENT
    currentUser = new UserDataBase(0, this);
#endif
}

UserData* UserDataBasePlugin::getUser(quint32 userId)
{
    if ( ! users.contains(userId))
        users[userId] = new UserDataBase(userId, this);

    return users[userId];
}

Data* UserDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getUser(tmpId);
}

#ifdef HORUS_CLIENT
void UserDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((UserDataBase*)(d))->id = tmpId;
}
#endif
#ifdef HORUS_SERVER
bool UserDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}

void UserDataBasePlugin::userDisconnected(UserData* TODO)
{
}

UserData* UserDataBasePlugin::authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password)
{
    if (login.length() > 32 || password.length() != SHA1_WORD_SIZE)
    {
        qDebug() << "UserDataBasePlugin::authenticatePassword Password is not a SHA1 hash.";
        return 0;
    }

    query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND password=?;");
    query.addBindValue(login);
    query.addBindValue(password.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataBasePlugin::authenticatePassword pair user/password not found in enabled users.";
        return 0;
    }

    UserData* user = getUser(query.value(0).toUInt());
    user->fillFromDatabase(query);
    user->setStatus(user, Data::UPTODATE);
    return user;
}

UserData* UserDataBasePlugin::authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& session)
{
    if (login.length() > 32 || session.length() != SESSION_WORD_SIZE)
    {
        qDebug() << "UserDataBasePlugin::authenticateSession Session key have an invalid size.";
        return 0;
    }

    query.prepare("SELECT id FROM users WHERE enabled=1 AND login=? AND session_key=?;");
    query.addBindValue(login);
    query.addBindValue(session.toHex());
    if ( ! query.exec() || ! query.next())
    {
        qDebug() << "UserDataBasePlugin::authenticateSession pair user/session not found in enabled users.";
        return 0;
    }

    UserData* user = getUser(query.value(0).toUInt());
    user->fillFromDatabase(query);
    user->setStatus(user, Data::UPTODATE);
    return user;
}
#endif
