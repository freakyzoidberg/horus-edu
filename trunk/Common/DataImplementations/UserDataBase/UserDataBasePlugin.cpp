#include "UserDataBasePlugin.h"
#include "UserDataBase.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

UserData* UserDataBasePlugin::getUser(quint32 userId)
{
    if ( ! users.contains(userId))
        users[userId] = new UserDataBase(userId, this);
    return users[userId];
}

QList<UserData*>     UserDataBasePlugin::getAllUser()
{
    return users.values();
}

Data* UserDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getUser(tmpId);
}

Data* UserDataBasePlugin::getNewData()
{
    static quint32 uniqueId = 0;
    return getUser(--uniqueId);
}

#ifdef HORUS_CLIENT
void UserDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((UserDataBase*)(d))->_id = tmpId;
}
#endif
#ifdef HORUS_SERVER
void UserDataBasePlugin::loadDataBase(QSqlQuery& query)
{
    query.prepare("SELECT id,login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users;");
    query.exec();
    while (query.next())
    {
        UserDataBase* user = (UserDataBase*)(getUser(query.value(0).toUInt()));
        user->_login       = query.value(1).toString();
        user->_level       = (UserLevel)(query.value(2).toUInt());
        user->_lastLogin   = query.value(3).toDateTime();
        user->_surname     = query.value(4).toString();
        user->_name        = query.value(5).toString();
        user->_birthDate   = query.value(6).toDateTime();
        user->_picture     = query.value(7).toByteArray();
        user->_address     = query.value(8).toString();
        user->_phone       = query.value(9).toString();
        user->_country     = query.value(10).toString();
        user->_language    = query.value(11).toString();
        TreeDataPlugin* treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
        if (treePlugin)
            user->_node = treePlugin->getNode( query.value(12).toUInt() );
        else
            user->_node = 0;
        user->_enabled     = query.value(13).toBool();
        user->_lastChange  = query.value(14).toDateTime();
        user->_status      = Data::UPTODATE;
    }
}

void UserDataBasePlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
    foreach (UserData* data, users)
        if (data->lastChange() >= date)
            dataManager->sendData(user, data);
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

    UserDataBase* user = (UserDataBase*)(getUser(query.value(0).toUInt()));
    user->fillFromDatabase(query);
    user->setStatus(Data::UPTODATE);
    user->updateLastLogin(query);
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

    UserDataBase* user = (UserDataBase*)(getUser(query.value(0).toUInt()));
    user->fillFromDatabase(query);
    user->setStatus(Data::UPTODATE);
    user->updateLastLogin(query);
    return user;
}
#endif
