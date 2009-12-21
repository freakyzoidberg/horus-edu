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
#include "MarksDataBasePlugin.h"
#include "MarksDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

MarksDataBasePlugin::MarksDataBasePlugin()
{
}

MarksData* MarksDataBasePlugin::newMarks(TreeData* parent, QString name, UserData* user)
{
	if ( ! user)
		user = pluginManager->currentUser();

	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->createNode();
	node->setParent(parent);
	node->setUser(user);
	node->setName(name);
	node->setType("MARKS");
	node->create();
	return nodeMarks(node);
}

MarksData* MarksDataBasePlugin::nodeMarks(TreeData* node)
{
	MarksData* Marks = node->registeredData<MarksData*>();
	if ( ! Marks)
	{
		Marks = new MarksDataBase(node, this);
		Marks->moveToThread(this->thread());
		_allDatas.append(Marks);
	}
	return Marks;
}

MarksData* MarksDataBasePlugin::nodeMarks(quint32 nodeId)
{
	return nodeMarks(pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId));
}

QList<MarksData*> MarksDataBasePlugin::userMarkss(UserData* user, const QDateTime from, const QDateTime to)
{
	QList<MarksData*> list;
	MarksData* Marks;
	//look in every parent nodes until the root node
	for (TreeData* node = user->studentClass()->parent(); node; node = node->parent());
	/*	if ((Marks = node->registeredData<MarksData*>()) && Marks->startTime() < to && Marks->endTime() > from)
			list.append(Marks); */

	//recursively look in every children nodes
	recursiveTreeSearch(list, user->studentClass(), from, to);

	return list;
}

QList<MarksData*> MarksDataBasePlugin::nodeMarkss(TreeData* node, const QDateTime from, const QDateTime to)
{
	QList<MarksData*> list;
	//recursively look in every children nodes
	recursiveTreeSearch(list, node, from, to);

	return list;
}

void MarksDataBasePlugin::recursiveTreeSearch(QList<MarksData*>& list, TreeData* node, const QDateTime& from, const QDateTime& to)
{
	MarksData* Marks;
/*	if ((Marks = node->registeredData<MarksData*>()) && Marks->startTime() < to && Marks->endTime() > from)
		list.append(Marks); */

	foreach (TreeData* child, node->children())
		recursiveTreeSearch(list, child, from, to);
}

Data* MarksDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return nodeMarks(pluginManager->findPlugin<TreeDataPlugin*>()->node(tmpId));
}

bool MarksDataBasePlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	if ( ! tree || ! tree->canLoad())
		return false;

#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS `StudentMarks` (\
`id` INT NOT NULL PRIMARY KEY ,\
`exam_id` INT NOT NULL ,\
`student_id` INT NOT NULL ,\
`comment` TEXT NOT NULL ,\
`result` VARCHAR( 16 ) NOT NULL\
);")
	||
		 ! query.exec("SELECT`exam_id`,`student_id`,`comment`,`result`FROM`StudentMarks`;")
		)
	{
		qDebug() << "MarksDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return Plugin::canLoad();
}

void  MarksDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`exam_id`,`student_id`,`comment`,`result`FROM`StudentMarks`;");
	query.exec();
	while (query.next())
	{
		MarksDataBase* Marks = (MarksDataBase*)(nodeMarks(pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(0).toUInt())));
		Marks->_result = query.value(3).toString();
		Marks->_comment = query.value(2).toString();
		//Marks->_exam   = query.value(2).toDateTime();
		Marks->_student = query.value(1).toInt();
		Marks->_status = Data::UPTODATE;
	}
#endif
	Plugin::load();
}

void  MarksDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (MarksDataBase*)d;
	_allDatas.clear();
	Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> MarksDataBasePlugin::datasForUpdate(UserData*, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allDatas)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
#ifdef HORUS_CLIENT
#include "../../../Client/DataListModel.cpp"
QAbstractListModel* MarksDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif
