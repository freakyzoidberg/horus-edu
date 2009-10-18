#include "EventDataBasePlugin.h"
#include "EventDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"

EventData* EventDataBasePlugin::getEvent(TreeData* node)
{
	if ( ! events.contains(node))
	{
		EventData* event = new EventDataBase(node, this);
		event->moveToThread(this->thread());
		events[ node ] = event;
	}
	return events.value(node);
}

EventData* EventDataBasePlugin::getEvent(quint32 nodeId)
{
	return getEvent(pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId));
}

Data* EventDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return getEvent(tmpId);
}

QList<Data*> EventDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, events)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}

#ifdef HORUS_SERVER
void EventDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id,start_time,end_time FROM event;");
    query.exec();
    while (query.next())
    {
		EventDataBase* event = (EventDataBase*)(getEvent(query.value(0).toUInt()));
		event->_startTime = query.value(1).toDateTime();
		event->_endTime   = query.value(1).toDateTime();
		event->_status = Data::UPTODATE;
    }
}

void EventDataBasePlugin::userConnected(UserData* user, QDateTime date)
{
	foreach (EventData* data, events)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
            dataManager->sendData(user, data);
}
#endif
