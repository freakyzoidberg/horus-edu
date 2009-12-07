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
#include "ScheduleDataBasePlugin.h"
#include "ScheduleDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

ScheduleDataBasePlugin::ScheduleDataBasePlugin()
{
}

ScheduleData* ScheduleDataBasePlugin::newSchedule(TreeData *node)
{
        static quint32 tmpId = 0;
        tmpId--;

        ScheduleDataBase* s = ((ScheduleDataBase*)( schedule(tmpId)) );
        s->_node = node;
        return s;
}

ScheduleData* ScheduleDataBasePlugin::schedule(quint32 scheduleId)
{
//        if (userId == 0)
//                return nobody();

        foreach (Data* d, _allDatas)
        {
                ScheduleDataBase* s = (ScheduleDataBase*)d;
                if (s->_id == scheduleId)
                        return s;
        }

        ScheduleDataBase* s = new ScheduleDataBase(scheduleId, this);

        s->_node = pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
        _allDatas.append(s);
        return s;
}

ScheduleData* ScheduleDataBasePlugin::schedule(TreeData* node)
{
        foreach (Data* d, _allDatas)
        {
                ScheduleDataBase* s = (ScheduleDataBase*)d;
                if (s->_node->id() == node->id())
                {
                    return s;
                }
        }
	return (0);
}


Data* ScheduleDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
        return schedule(tmpId);
}

bool ScheduleDataBasePlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	if ( ! tree || ! tree->canLoad())
		return false;
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
        if ( ! query.exec("CREATE TABLE IF NOT EXISTS `schedule`(\
                                                `id` int(11) NOT NULL AUTO_INCREMENT,\
                                                `id_node` int(11) NOT NULL,\
                                                `date_start` date NOT NULL,\
                                                `date_end` date NOT NULL,\
                                                `exception` blob,\
                                                PRIMARY KEY(`id`)\
					);")
		||
                 ! query.exec("SELECT`id`,`id_node`,`date_start`,`date_end`,`exception`FROM`schedule`WHERE`id`=-1;")
		)
	{
                qDebug() << "ScheduleDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return Plugin::canLoad();
}

void  ScheduleDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
        query.prepare("SELECT`id`,`id_node`,`date_start`,`date_end`,`exception`FROM`schedule`;");
	query.exec();
	while (query.next())
	{
                ScheduleDataBase* Schedule = (ScheduleDataBase*)(schedule(query.value(0).toUInt()));
                Schedule->_node = pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(1).toUInt());
                Schedule->_startDate = query.value(2).toDate();
                Schedule->_endDate   = query.value(3).toDate();
                QSqlQuery query2 = pluginManager->sqlQuery();
                query2.prepare("SELECT `id`, `id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher`, `color` FROM `schedule_event` WHERE `id_schedule`=? ORDER BY `id`;");
                query2.addBindValue(Schedule->_id);
                query2.exec();
                Schedule->_sEvents.clear();
                while (query2.next())
                {
                    Schedule->_sEvents.append(new ScheduleItem(query2.value(1).toInt(),
                                                                 query2.value(2).toInt(),
                                                                 query2.value(5).toString(),
                                                                 query2.value(3).toTime(),
                                                                 query2.value(4).toTime(),
                                                                 query2.value(6).toString(),
                                                                 query2.value(7).toDate(),
                                                                 query2.value(8).toDate(),
                                                                 query2.value(9).toInt(),
                                                                 query2.value(10).toBool(),
                                                                 query2.value(11).toInt(),
                                                                 query2.value(12).toString()));
                }
                //add exception
                //Schedule->_lastChange= query.value(4).toDateTime();
                Schedule->_status = Data::UPTODATE;

	}
#endif
	Plugin::load();
}

void  ScheduleDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
                delete (ScheduleDataBase*)d;
	_allDatas.clear();
	Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> ScheduleDataBasePlugin::datasForUpdate(UserData*, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allDatas)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
#ifdef HORUS_CLIENT
void ScheduleDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
        ScheduleDataBase* sch = ((ScheduleDataBase*)(d));
        s >> sch->_id;
        qDebug() << "Schedule data Have a New Key" << sch->_id;
}
#endif
