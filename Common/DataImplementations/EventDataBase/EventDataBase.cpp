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
#include "EventDataBase.h"
#include "EventDataBasePlugin.h"

#include "../../TreeData.h"

EventDataBase::EventDataBase(TreeData* node, EventDataBasePlugin* plugin) : EventData(plugin)
{
	_node = node;
	_node->registerData(this);
}

void EventDataBase::keyToStream(QDataStream& s) const
{
	s << _node->id();
}

void EventDataBase::dataToStream(QDataStream& s) const
{
	s << _startTime << _endTime << _comment;
}

void EventDataBase::dataFromStream(QDataStream& s)
{
	s >> _startTime >> _endTime >> _comment;
}

bool EventDataBase::canChange(UserData* user) const
{
	return _node->canChange(user);
}

bool EventDataBase::canAccess(UserData* user) const
{
	return _node->canAccess(user);
}

QDebug EventDataBase::operator<<(QDebug debug) const
{
	return debug << dataType() << _node->id() << _startTime << _endTime;
}

const QList<Data*> EventDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_node);
	return list;
}

#ifdef HORUS_SERVER
quint8 EventDataBase::serverCreate()
{
	QMutexLocker M(&_node->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`event`(`id_tree`,`start_time`,`end_time`,`comment`)VALUES(?,?,?);");
	query.addBindValue(_node->id());
	query.addBindValue(_startTime);
	query.addBindValue(_endTime);
	query.addBindValue(_comment);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	return NONE;
}

quint8 EventDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`event`SET`start_time`=?,`end_time`=?,`comment`=? WHERE`id_tree`=?;");
	query.addBindValue(_startTime);
	query.addBindValue(_endTime);
	query.addBindValue(_node->id());
	query.addBindValue(_comment);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 EventDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`event`WHERE`id_tree`=?;");
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
#ifdef HORUS_CLIENT
QVariant EventDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
		if (column == 0)
			return _node->name();
		if (column == 1)
			return _startTime;
		if (column == 2)
			return _endTime;
		if (column == 3)
			return _comment;
	}
   return Data::data(column, role);
}
#endif
