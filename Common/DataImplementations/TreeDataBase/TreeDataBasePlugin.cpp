#include "TreeDataBasePlugin.h"
#include "TreeDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"

TreeDataBasePlugin::TreeDataBasePlugin()
{
}

TreeData* TreeDataBasePlugin::getNode(quint32 nodeId)
{
    if ( ! nodes.contains(nodeId))
    {
        TreeData* node = new TreeDataBase(nodeId, this);
#ifdef HORUS_CLIENT
        node->moveToThread(this->thread());
#endif

        node->setParent(0);

        nodes[nodeId] = node;
    }
    return nodes[nodeId];
}

Data* TreeDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getNode(tmpId);
}

#ifdef HORUS_CLIENT
void TreeDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((TreeDataBase*)(d))->_id = tmpId;
}

#include "../../../Client/Plugins/TreeBaseClient/TreeModel.h"

QAbstractItemModel* TreeDataBasePlugin::getTreeModel()
{
    return new TreeModel(pluginManager);
}
#endif
#ifdef HORUS_SERVER
void TreeDataBasePlugin::loadDataBase(QSqlQuery& query)
{
    query.prepare("SELECT id,typeofnode,name,user_ref,id_parent FROM tree;");
    query.exec();
    while (query.next())
    {
        TreeDataBase* node = (TreeDataBase*)(getNode(query.value(0).toUInt()));
        node->_type   = query.value(1).toString();
        node->_name   = query.value(2).toString();
		node->_user   = pluginManager->findPlugin<UserDataPlugin*>()->getUser( query.value(3).toUInt() );
        node->_status = Data::UPTODATE;
        if (node->_id)
            node->setParent( getNode(query.value(4).toUInt()) );
		else
			node->setParent(0);
    }
}

void TreeDataBasePlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
    foreach (TreeData* data, nodes)
        if (data->lastChange() >= date)
            dataManager->sendData(user, data);
}
#endif
