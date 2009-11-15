#include "EventDataBasePlugin.h"
#include "EventDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

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
		_allEvents.append(event);
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

#ifdef HORUS_SERVER
void EventDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id,start_time,end_time FROM event;");
    query.exec();
    while (query.next())
    {
		EventDataBase* event = (EventDataBase*)(nodeEvent(pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(0).toUInt())));
		event->_startTime = query.value(1).toDateTime();
		event->_endTime   = query.value(1).toDateTime();
		event->_status = Data::UPTODATE;
    }
}

QList<Data*> EventDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allEvents)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
