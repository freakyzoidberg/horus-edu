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

ScheduleData* ScheduleDataBasePlugin::newSchedule(TreeData* parent/*, QString name, UserData* user*/)
{
//	if ( ! user)
//		user = pluginManager->currentUser();

	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->createNode();
	node->setParent(parent);
//	node->setUser(user);
//	node->setName(name);
        node->setType("SCHEDULE");
	node->create();
        return nodeSchedule(node);
}

ScheduleData* ScheduleDataBasePlugin::nodeSchedule(TreeData* node)
{
        ScheduleData* Schedule = node->registeredData<ScheduleData*>();
        if ( ! Schedule)
	{
                Schedule = new ScheduleDataBase(node, this);
                Schedule->moveToThread(this->thread());
                _allDatas.append(Schedule);
	}
        return Schedule;
}

ScheduleData* ScheduleDataBasePlugin::nodeSchedule(quint32 nodeId)
{
        return nodeSchedule(pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId));
}


QList<ScheduleData*> ScheduleDataBasePlugin::nodeSchedules(TreeData* node, const QDate from, const QDate to)
{
        QList<ScheduleData*> list;
	//recursively look in every children nodes
	recursiveTreeSearch(list, node, from, to);

	return list;
}

void ScheduleDataBasePlugin::recursiveTreeSearch(QList<ScheduleData*>& list, TreeData* node, const QDate& from, const QDate& to)
{
        ScheduleData* Schedule;
        if ((Schedule = node->registeredData<ScheduleData*>()) && Schedule->startDate() < to && Schedule->endDate() > from)
                list.append(Schedule);

	foreach (TreeData* child, node->children())
		recursiveTreeSearch(list, child, from, to);
}

Data* ScheduleDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
        return nodeSchedule(pluginManager->findPlugin<TreeDataPlugin*>()->node(tmpId));
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
                                                `exception` blob NOT NULL,\
					);")
		||
                 ! query.exec("SELECT`id`,`id_node`,`date_start`,`date_end`,`exception`FROM`schedule`WHERE`id_node`=-1;")
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
                ScheduleDataBase* Schedule = (ScheduleDataBase*)(nodeSchedule(pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(0).toUInt())));
                Schedule->_startDate = query.value(1).toDate();
                Schedule->_endDate   = query.value(2).toDate();
                //add exception
                Schedule->_lastChange= query.value(3).toDateTime();
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

