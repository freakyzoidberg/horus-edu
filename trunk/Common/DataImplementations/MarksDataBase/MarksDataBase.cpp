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
#include "MarksDataBase.h"
#include "MarksDataBasePlugin.h"

#include "../../TreeData.h"
#include "../../UserData.h"

MarksDataBase::MarksDataBase(quint32 id, MarksDataBasePlugin* plugin) : MarksData(id, plugin)
{
	moveToThread(plugin->thread());
}

void MarksDataBase::keyToStream(QDataStream& s) const
{
	s << _id;
}

void MarksDataBase::dataToStream(QDataStream& s) const
{
	s << _comment << _result << _student << _exam->id();
}

void MarksDataBase::dataFromStream(QDataStream& s)
{
	quint32	examId;

	s >> _comment >> _result >> _student >> examId;

	setExam(_plugin->pluginManager->findPlugin<ExamsDataPlugin*>()->exam(examId));
	Data::dataFromStream(s);
}

bool MarksDataBase::canChange(UserData* user) const
{
		return true;
}

bool MarksDataBase::canAccess(UserData* user) const
{
	return true;
}

QDebug MarksDataBase::operator<<(QDebug debug) const
{
	return debug << dataType() << _exam->id() << _comment << _student;
}

const QList<Data*> MarksDataBase::dependsOfCreatedData() const
{
  QList<Data*> list;
  list.append(_exam); 
       return list;
}

#ifdef HORUS_SERVER
quint8 MarksDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`exam_id`,`comment`,`result`,`student_id`FROM`Marks` `WHERE`id`=?");
	query.addBindValue(_id);
	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_comment	= query.value(1).toString();
	_result		= query.value(2).toString();
	_student	= query.value(3).toInt();
	this->_exam =
	_plugin->pluginManager->findPlugin<ExamsDataPlugin*>()->exam(query.value(0).toUInt());
	return NONE;
}

quint8 MarksDataBase::serverCreate()
{
	QMutexLocker M(&_exam->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`Marks`(`exam_id`,`comment`,`result`,`student_id`)VALUES(?,?,?, ?);");
	query.addBindValue(_exam->id());
	query.addBindValue(_comment);
	query.addBindValue(_result);
	query.addBindValue(_student);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	_id = query.lastInsertId().toUInt();
	return NONE;
}

quint8 MarksDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`Marks`SET`comment`=?,`result`=?,`exam_id`=? WHERE`id`=?;");
	query.addBindValue(_comment);
	query.addBindValue(_result);
	query.addBindValue(_exam->id());
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 MarksDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`Marks`WHERE`id`=?;");
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
#ifdef HORUS_CLIENT
QVariant MarksDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
		if (column == 0)
		  return _exam->id();
		if (column == 1)
			return _comment;
		if (column == 2)
			return _result;
		if (column == 3)
			return _student;
	}
   return Data::data(column, role);
}
#endif
