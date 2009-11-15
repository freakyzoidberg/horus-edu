#include "TreeDataBasePlugin.h"
#include "TreeDataBase.h"
#include <QtCore/QCoreApplication>

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
        node->moveToThread(this->thread());
        node->setParent(0);

        nodes[nodeId] = node;
    }
    return nodes[nodeId];
}

TreeData* TreeDataBasePlugin::createNewNode()
{
	static quint32 tmpId = 0;
	tmpId--;
	return getNode(tmpId);
}

Data* TreeDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getNode(tmpId);
}

QList<Data*> TreeDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, nodes)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}

#ifdef HORUS_CLIENT
void TreeDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	TreeDataBase* node = ((TreeDataBase*)(d));
	nodes.remove(node->_id);
	s >> node->_id;
	nodes.insert(node->_id, node);
	qDebug() << "Tree data Have a New Key" << node->_id;
}
#endif
#ifdef HORUS_SERVER
void TreeDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
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

void TreeDataBasePlugin::userConnected(UserData* user, QDateTime date)
{
    foreach (TreeData* data, nodes)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
            dataManager->sendData(user, data);
}
#endif