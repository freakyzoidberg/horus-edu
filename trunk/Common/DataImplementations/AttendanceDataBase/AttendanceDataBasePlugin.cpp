#include "AttendanceDataBasePlugin.h"
#include "AttendanceDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"



#ifdef HORUS_SERVER
void AttendanceDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id,start_time,end_time FROM event;");
    query.exec();
    while (query.next())
    {
                AttendanceDataBase* event = (AttendanceDataBase*)(nodeEvent(pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(0).toUInt())));
		event->_startTime = query.value(1).toDateTime();
		event->_endTime   = query.value(1).toDateTime();
		event->_status = Data::UPTODATE;
    }
}

QList<Data*> AttendanceDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allEvents)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
