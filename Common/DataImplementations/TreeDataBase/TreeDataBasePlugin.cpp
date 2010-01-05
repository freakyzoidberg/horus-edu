/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "TreeDataBasePlugin.h"
#include "TreeDataBase.h"
#include <QtCore/QCoreApplication>

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"
#ifdef HORUS_CLIENT
#include "../../../Client/DataListModel.h"
#include "../../../Client/Plugins/TreeBaseClient/Implementation/TreeModel.h"
#endif
TreeDataBasePlugin::TreeDataBasePlugin()
{
	_rootNode = new TreeDataBase(0, this);
}

void TreeDataBasePlugin::load()
{
	((TreeDataBase*)_rootNode)->_user = pluginManager->findPlugin<UserDataPlugin*>()->nobody();
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id`,`typeofnode`,`name`,`user_ref`,`id_parent`,`mtime`FROM`tree`;");
	query.exec();
	while (query.next())
	{
		TreeDataBase* n	= (TreeDataBase*)(node(query.value(0).toUInt()));
		n->_type		= query.value(1).toString();
		n->_name		= query.value(2).toString();
		n->_user		= pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(3).toUInt() );
		quint32 parentId= query.value(4).toUInt();
		if (parentId == n->_id)
			n->setParent(0);
		else
			n->setParent( node(parentId) );
		n->_lastChange	= query.value(5).toDateTime();
		n->_status		= Data::UPTODATE;
	}
#endif
#ifdef HORUS_CLIENT
	_listModel = new DataListModel(this);
	_treeModel = new TreeModel(this);
#endif
	Plugin::load();
}

void TreeDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete static_cast<TreeDataBase*>(d);
	_allDatas.clear();
	static_cast<TreeDataBase*>(_rootNode)->_children.clear();
#ifdef HORUS_CLIENT
	delete _listModel;
	delete _treeModel;
#endif
	DataPlugin::unload();
}

bool TreeDataBasePlugin::canLoad() const
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS`tree`(\
						`id`int(11) NOT NULL auto_increment,\
						`typeofnode`varchar(42) NOT NULL,\
						`name`varchar(128) NOT NULL,\
						`user_ref`int(11) NOT NULL,\
						`id_parent`int(11) NOT NULL,\
						`mtime`timestamp NOT NULL,\
						PRIMARY KEY(`id`)\
					);")
		||
		 ! query.exec("SELECT`id`,`typeofnode`,`name`,`user_ref`,`id_parent`,`mtime`FROM`tree`WHERE`id`=-1;")
		)
	{
		qDebug() << "TreeDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}

TreeData* TreeDataBasePlugin::node(quint32 nodeId)
{
	if ( ! nodeId)
		return _rootNode;

	foreach (Data* d, _allDatas)
	{
		TreeDataBase* n = static_cast<TreeDataBase*>(d);
		if (n->_id == nodeId)
			return n;
	}

	TreeDataBase* n = new TreeDataBase(nodeId, this);
	n->_user = pluginManager->findPlugin<UserDataPlugin*>()->nobody();
	n->connect(n->_user, SIGNAL(removed()), n, SLOT(userRemoved()));

	_allDatas.append(n);
	return n;
}

TreeData* TreeDataBasePlugin::createNode()
{
	static quint32 tmpId = 0;
	tmpId--;
	return node(tmpId);
}

QStringList TreeDataBasePlugin::subjects() const
{
	QStringList list;
	foreach (Data* d, _allDatas)
	{
		TreeDataBase* n = static_cast<TreeDataBase*>(d);
		if (n->type() == "SUBJECT" && ! list.contains(n->name()))
			list.append(n->name());
	}
	return list;
}

QList<TreeData*> TreeDataBasePlugin::grades() const
{
	QList<TreeData*> list;
	foreach (Data* d, _allDatas)
	{
		TreeDataBase* n = static_cast<TreeDataBase*>(d);
		if (n->type() == "GRADE")
			list.append(n);
	}
	return list;
}

Data* TreeDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return node(tmpId);
}

#ifdef HORUS_CLIENT
void TreeDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	TreeDataBase* n = ((TreeDataBase*)(d));
	s >> n->_id;
	qDebug() << "Tree data Have a New Key" << n->_id;
}
#endif
