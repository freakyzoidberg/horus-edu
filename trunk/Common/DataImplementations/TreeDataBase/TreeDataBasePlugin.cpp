#include "TreeDataBasePlugin.h"
#include "TreeDataBase.h"
#include <QtCore/QCoreApplication>

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"

TreeData* TreeDataBasePlugin::node(quint32 nodeId)
{
	if ( ! _nodes.contains(nodeId))
    {
		TreeDataBase* n = new TreeDataBase(nodeId, this);
		_nodes[nodeId] = n;
    }
	return _nodes[nodeId];
}

TreeData* TreeDataBasePlugin::createNode()
{
	static quint32 tmpId = 0;
	tmpId--;
	return node(tmpId);
}

Data* TreeDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return node(tmpId);
}

QList<Data*> TreeDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, _nodes)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}

#ifdef HORUS_CLIENT
void TreeDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	TreeDataBase* node = ((TreeDataBase*)(d));
	_nodes.remove(node->_id);
	s >> node->_id;
	_nodes.insert(node->_id, node);
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
		TreeDataBase* n = (TreeDataBase*)(node(query.value(0).toUInt()));
		n->_type   = query.value(1).toString();
		n->_name   = query.value(2).toString();
		n->_user   = pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(3).toUInt() );
		n->_status = Data::UPTODATE;
		if (n->_id)
			n->setParent( node(query.value(4).toUInt()) );
		else
			n->setParent(0);
    }
}

QList<Data*> TreeDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (TreeData* data, _nodes)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
