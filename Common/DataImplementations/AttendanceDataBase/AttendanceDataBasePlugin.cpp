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
#include "AttendanceDataBasePlugin.h"
#include "AttendanceDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"




AttendanceData* AttendanceDataBasePlugin::newAttendance(UserData* parent, QDate date, QString lesson)
{
        static quint32 tmpId = 0;
        tmpId--;

        AttendanceDataBase* s = ((AttendanceDataBase*)( attendance(tmpId)) );
        s->_user = parent;
        s->_date = date;
        return s;
}

AttendanceData* AttendanceDataBasePlugin::attendance(quint32 attendanceId)
{
//        if (userId == 0)
//                return nobody();

        foreach (Data* d, _allDatas)
        {
                AttendanceDataBase* a = (AttendanceDataBase*)d;
                if (a->_id == attendanceId)
                        return a;
        }

        AttendanceDataBase* a = new AttendanceDataBase(attendanceId, this);

//        a->_node = pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
        _allDatas.append(a);
        return a;
}

QList<AttendanceData* > AttendanceDataBasePlugin::attendance(UserData* node)
{
        QList<AttendanceData* > listAttendance;
        foreach (Data* d, _allDatas)
        {
                AttendanceDataBase* s = (AttendanceDataBase*)d;
                if (s->_user->id() == node->id())
                {
                    listAttendance.append(s);
                }
        }
//        if (listAttendance.size() == 0)
            return listAttendance;
}


Data* AttendanceDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
        return attendance(tmpId);
}

bool AttendanceDataBasePlugin::canLoad() const
{
        UserDataPlugin* user = pluginManager->findPlugin<UserDataPlugin*>();
        if ( ! user || ! user->canLoad())
                return false;
//        ScheduleDataPlugin* schedule = pluginManager->findPlugin<ScheduleDataPlugin*>();
//        if ( ! schedule || ! schedule->canLoad())
//                return false;
#ifdef HORUS_SERVER
        QSqlQuery query = pluginManager->sqlQuery();
        if ( ! query.exec("CREATE TABLE IF NOT EXISTS `attendance`(\
                                                                   `id` int(11) NOT NULL AUTO_INCREMENT,\
                                                                   `date` date NOT NULL,\
                                                                   `id_user` int(11) NOT NULL,\
                                                                   `lesson` text NOT NULL,\
                                                                   `type` int(11) NOT NULL,\
                                                                   `start_time` time NOT NULL,\
                                                                   `end_time` time NOT NULL,\
                                                                    KEY`id`(`id`)\
                                                                    );")
                ||
                 ! query.exec("SELECT`id`,`date`,`id_user`,`lesson`,`type`, `start_time`, `end_time` FROM `attendance` WHERE `id`=-1;")
                )
        {
                qDebug() << "AttendanceDataBasePlugin::canLoad()" << query.lastError();
                return false;
        }
#endif
        return Plugin::canLoad();
}

void  AttendanceDataBasePlugin::load()
{
#ifdef HORUS_SERVER
        QSqlQuery query = pluginManager->sqlQuery();
        query.prepare("SELECT`id`,`date`,`id_user`,`lesson`,`type`, `start_time`, `end_time` FROM `attendance`;");
        query.exec();
        while (query.next())
        {
                AttendanceDataBase* a = (AttendanceDataBase*)(attendance(query.value(0).toUInt()));
                a->_date = query.value(1).toDate();
//                attendance->_idUser = query.value(2).toUInt();
//                attendance->_idSchedule = query.value(3).toUInt();
                a->_user = pluginManager->findPlugin<UserDataPlugin*>()->user(query.value(2).toUInt());
                a->_lesson = query.value(3).toString();
                a->_type = query.value(4).toInt();
                a->_startTime = query.value(5).toTime();
                a->_endTime   = query.value(6).toTime();
                a->_status = Data::UPTODATE;
        }
#endif
        Plugin::load();
}

void  AttendanceDataBasePlugin::unload()
{
        foreach (Data* d, _allDatas)
                delete (AttendanceDataBase*)d;
        _allDatas.clear();
        Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> AttendanceDataBasePlugin::datasForUpdate(UserData*, QDateTime date)
{
        QList<Data*> list;
        foreach (Data* data, _allDatas)
                if (data->lastChange() >= date && data->status() == Data::UPTODATE)
                        list.append(data);
        return list;
}
#endif
#ifdef HORUS_CLIENT
void AttendanceDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
        AttendanceDataBase* sch = ((AttendanceDataBase*)(d));
        s >> sch->_id;
        qDebug() << "Attendance data Have a New Key" << sch->_id;
}
#endif

