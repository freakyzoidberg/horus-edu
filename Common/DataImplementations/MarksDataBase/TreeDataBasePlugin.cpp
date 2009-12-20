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
