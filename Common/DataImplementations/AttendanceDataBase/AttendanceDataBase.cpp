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
#include "AttendanceDataBase.h"
#include "AttendanceDataBasePlugin.h"

#include "../../TreeData.h"

AttendanceDataBase::AttendanceDataBase(quint32 id, AttendanceDataBasePlugin* plugin) : AttendanceData(id, plugin)
{
//	_user = user;
//        _schedule = schedule;
}

void AttendanceDataBase::keyToStream(QDataStream &s) const
{
        s << _id;
}

void AttendanceDataBase::dataToStream(QDataStream &s) const
{
    s <<  _date << _user->id() << _schedule->id() << _type << _startTime << _endTime;
}

void AttendanceDataBase::dataFromStream(QDataStream &s)
{
    int id = 0;
    s >>  _date >> id;
    _user = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user(id);
    s >> id;
    _schedule = _plugin->pluginManager->findPlugin<ScheduleDataPlugin*>()->schedule(id);
    s >> _type >> _startTime >> _endTime;
}

QDebug AttendanceDataBase::operator<<(QDebug debug) const
{
	return (qDebug());
}

bool AttendanceDataBase::canAccess(UserData* user) const
{
    return true;
}


const QList<Data*> AttendanceDataBase::dependsOfCreatedData() const
{
        QList<Data*> list;
        list.append(_user);
        return list;
}


#ifdef HORUS_SERVER
quint8 AttendanceDataBase::serverCreate()
{
        QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("INSERT INTO`attendance`(`date`,`id_user`,`id_event`,`type`, `start_time`, `end_time`)VALUES(?,?,?,?,?,?);");
        query.addBindValue(_date);
        query.addBindValue(_user->id());
        query.addBindValue(_schedule->id());
        query.addBindValue(_type);
        query.addBindValue(_startTime);
        query.addBindValue(_endTime);
        if ( ! query.exec())
        {
                qDebug() << query.lastError();
                return DATABASE_ERROR;
        }
        _id = query.lastInsertId().toUInt();
         return NONE;
}

quint8 AttendanceDataBase::serverSave()
{
        QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("UPDATE`attendance`SET`date`=?,`id_user`=?,`id_event`=?,`type`=?, `start_time`=?, `end_time`=? WHERE`id`=?;");
        query.addBindValue(_date);
        query.addBindValue(_user->id());
        query.addBindValue(_schedule->id());
        query.addBindValue(_type);
        query.addBindValue(_startTime);
        query.addBindValue(_endTime);

        query.addBindValue(_id);
        if ( ! query.exec())
        {
                qDebug() << query.lastError();
                return DATABASE_ERROR;
        }
        return NONE;
}

quint8 AttendanceDataBase::serverRemove()
{
        QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("DELETE FROM`attendance`WHERE`id`=?;");
        query.addBindValue(_id);
        if ( ! query.exec())
        {
                qDebug() << query.lastError();
                return DATABASE_ERROR;
        }
        if ( ! query.numRowsAffected())
                return NOT_FOUND;
        return NONE;
}
#endif
