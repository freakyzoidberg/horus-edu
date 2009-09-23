#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

WhiteBoardData* WhiteBoardDataPlugin::getWhiteBoard(TreeData* node)
{
//    if ( ! users.contains(userId))
//		users[userId] = new WhiteBoardData(userId, this);
//    return users[userId];
}

Data* WhiteBoardDataPlugin::getDataWithKey(QDataStream& s)
{
//    quint32 tmpId;
//    s >> tmpId;
//    return getUser(tmpId);
}

#ifdef HORUS_CLIENT
void WhiteBoardDataPlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
//    quint32 tmpId;
//    s >> tmpId;
//	((WhiteBoardData*)(d))->_id = tmpId;
}
#endif
#ifdef HORUS_SERVER
void WhiteBoardDataPlugin::loadDataBase(QSqlQuery& query)
{
//    query.prepare("SELECT id,login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users;");
//    query.exec();
//    while (query.next())
//    {
//		WhiteBoardData* user = (WhiteBoardData*)(getUser(query.value(0).toUInt()));
//        user->_login       = query.value(1).toString();
//        user->_level       = (UserLevel)(query.value(2).toUInt());
//        user->_lastLogin   = query.value(3).toDateTime();
//        user->_surname     = query.value(4).toString();
//        user->_name        = query.value(5).toString();
//        user->_birthDate   = query.value(6).toDate();
//        user->_picture     = query.value(7).toByteArray();
//        user->_address     = query.value(8).toString();
//        user->_phone       = query.value(9).toString();
//        user->_country     = query.value(10).toString();
//        user->_language    = query.value(11).toString();
//        TreeDataPlugin* treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
//        if (treePlugin)
//            user->_node = treePlugin->getNode( query.value(12).toUInt() );
//        else
//            user->_node = 0;
//        user->_enabled     = query.value(13).toBool();
//        user->_lastChange  = query.value(14).toDateTime();
//        user->_status      = Data::UPTODATE;
//    }
}

void WhiteBoardDataPlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
//    foreach (UserData* data, users)
//        if (data->lastChange() >= date)
//            dataManager->sendData(user, data);
}
#endif
