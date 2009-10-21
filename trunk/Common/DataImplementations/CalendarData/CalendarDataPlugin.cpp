#include "CalendarDataPlugin.h"
#include "CalendarData.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

CalendarData* CalendarDataPlugin::getCalendar(TreeData* node)
{
        foreach (CalendarData* wb, whiteBoards)
		if (qobject_cast<TreeData *>(wb->node()) == node)
			return wb;

        CalendarData* wb = new CalendarData(node, this);
#ifdef HORUS_CLIENT
	wb->moveToThread(this->thread());
#endif
	whiteBoards.append(wb);
	return wb;
}

CalendarData* CalendarDataPlugin::getCalendar(quint32 nodeId)
{
        return getCalendar( pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId) );
}

Data* CalendarDataPlugin::getDataWithKey(QDataStream& s)
{
	quint32 nodeId;
	s >> nodeId;
        return getCalendar(nodeId);
}

QList<Data*> CalendarDataPlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, whiteBoards)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_SERVER
void CalendarDataPlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id_tree,mode,items,mtime FROM white_board;");
	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	while (query.next())
	{
                CalendarData* wb	= getCalendar(query.value(0).toUInt());
                wb->_syncMode		= (CalendarData::SyncMode)(query.value(1).toUInt());
		wb->_items			= query.value(2).toByteArray();
		wb->_lastChange		= query.value(3).toDateTime();
		wb->_status			= Data::UPTODATE;
	}
}

void CalendarDataPlugin::userConnected(UserData* user, QDateTime date)
{
        foreach (CalendarData* data, whiteBoards)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			dataManager->sendData(user, data);
}
#endif
