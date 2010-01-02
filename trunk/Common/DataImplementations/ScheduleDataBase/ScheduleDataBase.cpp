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

ScheduleDataBase::ScheduleDataBase(quint32 id, ScheduleDataBasePlugin* plugin) :  ScheduleData(id, plugin)
{
}

void ScheduleDataBase::keyToStream(QDataStream& s) const
{
	s << _id;
}

void ScheduleDataBase::dataToStream(QDataStream& s) const
{
	s << _startDate << _endDate << _node->id();

	QByteArray bufItems;
	QDataStream ds(&bufItems, QIODevice::WriteOnly);

	foreach (ScheduleItem* item, _sEvents)
		*item >> ds;
	s << bufItems;

        bufItems.clear();
	foreach (ScheduleException* item, _sException)
		*item >> ds;
	s << bufItems;

	Data::dataToStream(s);
}

void ScheduleDataBase::dataFromStream(QDataStream& s)
{
	quint32 nodeId;
	s >> _startDate >> _endDate >> nodeId;
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);

	QByteArray bufItems;


	s >> bufItems;
        QDataStream ds(bufItems);
        ScheduleItem* event;
        while ((_sEvents.count() > 0) && (event = _sEvents.takeFirst()))
		delete event;

	while ( ! ds.atEnd())
		_sEvents.append( new ScheduleItem(ds) );
        bufItems.clear();
	s >> bufItems;
        QDataStream ds2(bufItems);
	ScheduleException* exeption;
        while ((_sException.count() > 0) &&  (exeption = _sException.takeFirst()))
		delete exeption;
        while ( ! ds2.atEnd())
                _sException.append(new ScheduleException(ds2) );

	Data::dataFromStream(s);
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
        query.prepare("SELECT`date_start`,`date_end`,`id`FROM`schedule`WHERE`id_node`=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

        _id             = query.value(2).toInt();
        _startDate	= query.value(0).toDate();
        _endDate	= query.value(1).toDate();
        QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
        query2.prepare("SELECT `id`, `id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher` `color` FROM `schedule_event` WHERE `id_schedule`=? ORDER BY `id`;");
        query2.addBindValue(_id);
        _sEvents.clear();
        while (query2.next())
        {
            _sEvents.append(new ScheduleItem(query2.value(1).toInt(),
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
        QSqlQuery query3 = _plugin->pluginManager->sqlQuery();
        query3.prepare("SELECT`id_event`, `id_schedule`, `date_start`,`date_end`,`name`, `type` FROM `schedule`WHERE`id_schedule`=?;");
        query3.addBindValue(_id);
        query3.exec();
        _sException.clear();
        while(query3.next())
        {
            if (query3.value(5).toInt() == 1)
            {
                _sException.append(new ScheduleException(query3.value(2).toDate(), query3.value(3).toDate(), query3.value(4).toString()));
            }
            else if (query3.value(5).toInt() == 2)
            {
                _sEvents.at(query3.value(0).toInt())->addExcp(new ScheduleException(query3.value(2).toDate(), query3.value(3).toDate(), query3.value(4).toString()));
            }

        }
        return NONE;
}

quint8 ScheduleDataBase::serverCreate()
{
	QMutexLocker M(&_node->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("INSERT INTO`schedule`(`id_node`,`date_start`,`date_end`)VALUES(?,?,?);");
	query.addBindValue(_node->id());
        query.addBindValue(_startDate);
        query.addBindValue(_endDate);
        //query.addBindValue(_sException);

	if ( ! query.exec())
	{
                qDebug() << __FILE__ << __LINE__ ;
                qDebug()  <<query.lastError();
		return DATABASE_ERROR;
	}
        _id = query.lastInsertId().toUInt();
        qDebug() << _id;
        if (_sEvents.count() > 0)
        {
            for(int i = 0; i < _sEvents.count(); i++)
            {
                QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
                query2.prepare("INSERT INTO`schedule_event`(`id`, `id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher`, `color`)VALUES(?,?,?,?,?,?,?,?,?,?,?,?);");
                query2.addBindValue(i);
                query2.addBindValue(_id);
                query2.addBindValue(_sEvents.at(i)->getJWeek());
                query2.addBindValue(_sEvents.at(i)->getHStart());
                query2.addBindValue(_sEvents.at(i)->getHEnd());
                query2.addBindValue(_sEvents.at(i)->getName());
                query2.addBindValue(_sEvents.at(i)->getDetails());
                query2.addBindValue(_sEvents.at(i)->getSDate());
                query2.addBindValue(_sEvents.at(i)->getEDate());
                query2.addBindValue(_sEvents.at(i)->getModulo());
                query2.addBindValue(_sEvents.at(i)->getForce());
                query2.addBindValue(_sEvents.at(i)->getTeacher());
                query2.addBindValue(_sEvents.at(i)->getColor());
                if (_sEvents.at(i)->exceptions().count() > 0)
                {
                    for(int y = 0; y < _sEvents.at(i)->exceptions().count(); y++)
                    {
                        QSqlQuery query3 = _plugin->pluginManager->sqlQuery();
                        query3.prepare("INSERT INTO`schedule_exception`(`id_event`, `id_schedule`,`date_start`,`date_end`, `name`, `type`)VALUES(?,?,?,?,?,?);");
                        query3.addBindValue(i);
                        query3.addBindValue(_id);
                        query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->dateStart);
                        query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->dateEnd);
                        query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->name);
                        query3.addBindValue(2);
                    }
                }
                if ( ! query2.exec())
                {
                            qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query2.lastError();
                    return DATABASE_ERROR;
                }
            }
        }
        if (_sException.count() > 0)
        {
            for(int y = 0; y < _sException.count(); y++)
            {
                QSqlQuery query7 = _plugin->pluginManager->sqlQuery();
                query7.prepare("INSERT INTO`schedule_exception`(`id_event`, `id_schedule`,`date_start`,`date_end`, `name`, `type`)VALUES(?,?,?,?,?,?);");
                query7.addBindValue(-1);
                query7.addBindValue(_id);
                query7.addBindValue(_sException.at(y)->dateStart);
                query7.addBindValue(_sException.at(y)->dateEnd);
                query7.addBindValue(_sException.at(y)->name);
                query7.addBindValue(1);
                if ( ! query7.exec())
                {
                            qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query7.lastError();
                    return DATABASE_ERROR;
                }
            }
        }
        return NONE;
}

quint8 ScheduleDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("UPDATE`schedule`SET`date_start`=?,`date_end`=? WHERE`id_node`=?;");
        query.addBindValue(_startDate);
        query.addBindValue(_endDate);
        //query.addBindValue(_sException);
        query.addBindValue(_node->id());

	if ( ! query.exec())
	{
                    qDebug() << __FILE__ << __LINE__ ;
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
        QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
        query2.prepare("DELETE FROM`schedule_event`WHERE`id_schedule`=?;");
        query2.addBindValue(_id);
        if ( ! query2.exec())
        {
                    qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query2.lastError();
                    return DATABASE_ERROR;
        }
        QSqlQuery query4 = _plugin->pluginManager->sqlQuery();
        query4.prepare("DELETE FROM`schedule_exception`WHERE`id_schedule`=?;");
        query4.addBindValue(_id);
        if ( ! query4.exec())
        {
                    qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query4.lastError();
                    return DATABASE_ERROR;
        }
        if (_sEvents.count() > 0)
        {
            for(int i = 0; i < _sEvents.count(); i++)
            {

                    QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
                    query2.prepare("INSERT INTO`schedule_event`(`id`, `id_schedule`, `day`, `time_start`, `time_end`, `name`, `detail`, `date_start`, `date_end`, `modulo`, `force`, `id_teacher`, `color`)VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);");
                    query2.addBindValue(i);
                    query2.addBindValue(_id);
                    query2.addBindValue(_sEvents.at(i)->getJWeek());
                    query2.addBindValue(_sEvents.at(i)->getHStart());
                    query2.addBindValue(_sEvents.at(i)->getHEnd());
                    query2.addBindValue(_sEvents.at(i)->getName());
                    query2.addBindValue(_sEvents.at(i)->getDetails());
                    query2.addBindValue(_sEvents.at(i)->getSDate());
                    query2.addBindValue(_sEvents.at(i)->getEDate());
                    query2.addBindValue(_sEvents.at(i)->getModulo());
                    query2.addBindValue(_sEvents.at(i)->getForce());
                    query2.addBindValue(_sEvents.at(i)->getTeacher());
                    query2.addBindValue(_sEvents.at(i)->getColor());
                    if (_sEvents.at(i)->exceptions().count() > 0)
                    {
                        for(int y = 0; y < _sEvents.at(i)->exceptions().count(); y++)
                        {
                            QSqlQuery query3 = _plugin->pluginManager->sqlQuery();
                            query3.prepare("INSERT INTO`schedule_exception`(`id_event`, `id_schedule`,`date_start`,`date_end`, `name`, `type`)VALUES(?,?,?,?,?,?);");
                            query3.addBindValue(i);
                            query3.addBindValue(_id);
                            query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->dateStart);
                            query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->dateEnd);
                            query3.addBindValue(_sEvents.at(i)->exceptions().at(y)->name);
                            query3.addBindValue(2);
                            if ( ! query3.exec())
                            {
                                        qDebug() << __FILE__ << __LINE__ ;
                                qDebug() << query3.lastError();
                                return DATABASE_ERROR;
                            }
                        }
                    }
                    if ( ! query2.exec())
                    {
                                qDebug() << __FILE__ << __LINE__ ;
                        qDebug() << query2.lastError();
                        return DATABASE_ERROR;
                    }
            }
        }
        if (_sException.count() > 0)
        {
            for(int y = 0; y < _sException.count(); y++)
            {
                QSqlQuery query7 = _plugin->pluginManager->sqlQuery();
                query7.prepare("INSERT INTO`schedule_exception`(`id_event`, `id_schedule`,`date_start`,`date_end`, `name`, `type`)VALUES(?,?,?,?,?,?);");
                query7.addBindValue(-1);
                query7.addBindValue(_id);
                query7.addBindValue(_sException.at(y)->dateStart);
                query7.addBindValue(_sException.at(y)->dateEnd);
                query7.addBindValue(_sException.at(y)->name);
                query7.addBindValue(1);
                if ( ! query7.exec())
                {
                            qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query7.lastError();
                    return DATABASE_ERROR;
                }
            }
        }
	return NONE;
}

quint8 ScheduleDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
        query.prepare("DELETE FROM`schedule`WHERE`id`=?;");
        query.addBindValue(_id);
	if ( ! query.exec())
	{
                    qDebug() << __FILE__ << __LINE__ ;
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
        if ( ! query.numRowsAffected())
                return NOT_FOUND;
        QSqlQuery query2 = _plugin->pluginManager->sqlQuery();
        query2.prepare("DELETE FROM`schedule_event`WHERE`id_schedule`=?;");
        query2.addBindValue(_id);
        if ( ! query2.exec())
        {
                    qDebug() << __FILE__ << __LINE__ ;
                    qDebug() << query2.lastError();
                    return DATABASE_ERROR;
        }
	return NONE;
}
#endif
