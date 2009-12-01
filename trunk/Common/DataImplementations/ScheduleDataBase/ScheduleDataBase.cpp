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
#include "ScheduleDataBase.h"
#include "ScheduleDataBasePlugin.h"

#include "../../TreeData.h"

ScheduleDataBase::ScheduleDataBase(TreeData* node, ScheduleDataBasePlugin* plugin) : ScheduleData(plugin)
{
	_node = node;
	_node->registerData(this);
}

void ScheduleDataBase::keyToStream(QDataStream& s) const
{
	s << _node->id();
}

void ScheduleDataBase::dataToStream(QDataStream& s) const
{
        s << _startDate << _endDate ;
        s << _sEvents;
        s << _sException;
}

void ScheduleDataBase::dataFromStream(QDataStream& s)
{
    s >> _startDate >> _endDate ;
    QByteArray bufItems;
    s >> bufItems;
    _sEvents.clear();
    QDataStream ds(bufItems);
    while ( ! ds.atEnd())
        _sEvents.append(new ScheduleItem(ds) );
    s >> bufItems;
    _sException.clear();
    QDataStream ds2(bufItems);
    while ( ! ds2.atEnd())
        _sException.append(new ScheduleException(ds2) );
}


bool ScheduleDataBase::canChange(UserData* user) const
{
	return _node->canChange(user);
}

bool ScheduleDataBase::canAccess(UserData* user) const
{
	return _node->canAccess(user);
}


QDebug ScheduleDataBase::operator<<(QDebug debug) const
{
        return debug << dataType() << _node->id() << _startDate << _endDate;
}

const QList<Data*> ScheduleDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_node);
	return list;
}

#ifdef HORUS_SERVER
quint8 ScheduleDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("SELECT`start_date`,`end_date`,`id`FROM`schedule`WHERE`id_tree`=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

        int  id         = query.value(0).toInt();
        _startDate	= query.value(1).toDate();
        _endDate	= query.value(2).toDate();
        query2 = _plugin->pluginManager->sqlQuery();
        query2.prepare("SELECT `id`, `id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher` FROM `schedule_event` WHERE `id_schedule`=?;");
        query2.addBindValue(id);
        _sEvents.clear();
        while (query2.next())
        {
            _sEvents.append(new ScheduleItem(query2.value(0).toInt(),
                                             query2.value(1).toInt(),
                                             query2.value(2).toInt(),
                                             query2.value(5).toString(),
                                             query2.value(3).toTime(),
                                             query2.value(4).toTime(),
                                             query2.value(6).toString(),
                                             query2.value(7).toDate(),
                                             query2.value(8).toDate(),
                                             query2.value(9).toInt(),
                                             query2.value(10).toBool(),
                                             query2.value(10).toInt()));

        }
	return NONE;
}

quint8 ScheduleDataBase::serverCreate()
{
	QMutexLocker M(&_node->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("INSERT INTO`schedule`(`id_node`,`start_date`,`end_date`,`exception`)VALUES(?,?,?,?);");
	query.addBindValue(_node->id());
        query.addBindValue(_startDate);
        query.addBindValue(_endDate);
//        query.addBindValue(_sException);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
        int id = query.lastInsertId().toUInt();
        for(int i = 0; i < _sEvents.count(); i++)
        {
            QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
            query2.prepare("INSERT INTO`schedule_event`(`id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher`)VALUES(?,?,?,?,?,?,?,?,?,?);");
            query2.addBindValue(id);
            query2.addBindValue(_sEvents.at(i)->getJWeek());
            query2.addBindValue(_sEvents.at(i)->getHStart())
            query2.addBindValue(_sEvents.at(i)->getHEnd());
            query2.addBindValue(_sEvents.at(i)->getName());
            query2.addBindValue(_sEvents.at(i)->getDetails());
            query2.addBindValue(_sEvents.at(i)->getSDate());
            query2.addBindValue(_sEvents.at(i)->getEDate());
            query2.addBindValue(_sEvents.at(i)->getModulo());
            query2.addBindValue(_sEvents.at(i)->getForce());
            query2.addBindValue(_sEvents.at(i)->getTeacher());
        }
        return NONE;
}

quint8 ScheduleDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("UPDATE`schedule`SET`start_date`=?,`end_date`=?,`exception`=? WHERE`id_node`=?;");
        query.addBindValue(_startDate);
        query.addBindValue(_endDate);
//add exception
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 ScheduleDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("DELETE FROM`schedule`WHERE`id_node`=?;");
	query.addBindValue(_node->id());

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
