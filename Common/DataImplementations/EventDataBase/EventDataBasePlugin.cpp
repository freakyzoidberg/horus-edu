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
#include "EventDataBasePlugin.h"
#include "EventDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

EventDataBasePlugin::EventDataBasePlugin()
{
}

EventData* EventDataBasePlugin::newEvent(TreeData* parent, QString name, UserData* user)
{
	if ( ! user)
		user = pluginManager->currentUser();

	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->createNode();
	node->setParent(parent);
	node->setUser(user);
	node->setName(name);
	node->setType("EVENT");
	node->create();
	return nodeEvent(node);
}

EventData* EventDataBasePlugin::nodeEvent(TreeData* node)
{
	EventData* event = node->registeredData<EventData*>();
	if ( ! event)
	{
		event = new EventDataBase(node, this);
		event->moveToThread(this->thread());
		_allDatas.append(event);
	}
	return event;
}

EventData* EventDataBasePlugin::nodeEvent(quint32 nodeId)
{
	return nodeEvent(pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId));
}

QList<EventData*> EventDataBasePlugin::userEvents(UserData* user, const QDateTime from, const QDateTime to)
{
	QList<EventData*> list;
	EventData* event;
	//look in every parent nodes until the root node
	for (TreeData* node = user->studentClass()->parent(); node; node = node->parent())
		if ((event = node->registeredData<EventData*>()) && event->startTime() < to && event->endTime() > from)
			list.append(event);

	//recursively look in every children nodes
	recursiveTreeSearch(list, user->studentClass(), from, to);

	return list;
}

QList<EventData*> EventDataBasePlugin::nodeEvents(TreeData* node, const QDateTime from, const QDateTime to)
{
	QList<EventData*> list;
	//recursively look in every children nodes
	recursiveTreeSearch(list, node, from, to);

	return list;
}

void EventDataBasePlugin::recursiveTreeSearch(QList<EventData*>& list, TreeData* node, const QDateTime& from, const QDateTime& to)
{
	EventData* event;
	if ((event = node->registeredData<EventData*>()) && event->startTime() < to && event->endTime() > from)
		list.append(event);

	foreach (TreeData* child, node->children())
		recursiveTreeSearch(list, child, from, to);
}

Data* EventDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return nodeEvent(pluginManager->findPlugin<TreeDataPlugin*>()->node(tmpId));
}

bool EventDataBasePlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	if ( ! tree || ! tree->canLoad())
		return false;

#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS `event`(\
						`id_tree` int(11) NOT NULL,\
						`start_time` timestamp NOT NULL,\
						`end_time` timestamp NOT NULL,\
						`comment` text NULL,\
						`mtime` timestamp NOT NULL,\
						PRIMARY KEY (`id_tree`)\
					);")
		||
		 ! query.exec("SELECT`id_tree`,`start_time`,`end_time`,`mtime`FROM`event`WHERE`id_tree`=-1;")
		)
	{
		qDebug() << "EventDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return Plugin::canLoad();
}

void  EventDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id_tree`,`start_time`,`end_time`,`comment`,`mtime`FROM`event`;");
	query.exec();
	while (query.next())
	{
		EventDataBase* event = (EventDataBase*)(nodeEvent(pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(0).toUInt())));
		event->_startTime = query.value(1).toDateTime();
		event->_endTime   = query.value(2).toDateTime();
		event->_lastChange= query.value(3).toDateTime();
		event->_status = Data::UPTODATE;
	}
#endif
	Plugin::load();
}

void  EventDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (EventDataBase*)d;
	_allDatas.clear();
	Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> EventDataBasePlugin::datasForUpdate(UserData*, QDateTime date)
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
QAbstractListModel* EventDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif
