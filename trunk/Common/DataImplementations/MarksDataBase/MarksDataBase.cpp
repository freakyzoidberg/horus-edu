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

MarksDataBase::MarksDataBase(TreeData* node, MarksDataBasePlugin* plugin) : MarksData(plugin)
{
	//_exam = ;
	//_exam->registerData(this);
}

void MarksDataBase::keyToStream(QDataStream& s) const
{
	//s << _;
}

void MarksDataBase::dataToStream(QDataStream& s) const
{
	s << _result << _comment << _date;
}

void MarksDataBase::dataFromStream(QDataStream& s)
{
	s >> _result >> _comment >> _date;
}

bool MarksDataBase::canChange(UserData* user) const
{
	return _exam->canChange(user);
}

bool MarksDataBase::canAccess(UserData* user) const
{
	return _exam->canAccess(user);
}

QDebug MarksDataBase::operator<<(QDebug debug) const
{
	return debug << dataType() << _result << _comment;
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
	query.prepare("SELECT`student_id`,`comment`,`result`FROM`StudentMarks`WHERE`exam_id`=?;");
//	query.addBindValue(_exam->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_student	= query.value(0).toInt();
	_comment	= query.value(1).toString();
	_result		= query.value(2).toString();

	return NONE;
}

quint8 MarksDataBase::serverCreate()
{
	//QMutexLocker M(&_node->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`StudentMarks`(`exam_id`,`student_id`,`comment`,`result`)VALUES(?,?,?,?);");
	//query.addBindValue(_exam->id());
	query.addBindValue(_student);
	query.addBindValue(_comment);
	query.addBindValue(_result);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	return NONE;
}

quint8 MarksDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`StudentMarks`SET`exam_id`=?,`student_id`=?,`comment`=?,`result`=? WHERE`exam_id`=?;");
	//query.addBindValue(_exam->id());
	query.addBindValue(_student);
	query.addBindValue(_comment);
	query.addBindValue(_result);
	//query.addBindValue(_exam->id());

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
	query.prepare("DELETE FROM`StudentMarks`WHERE`exam_id`=?;");
	//query.addBindValue(_exam->id());

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
	/*	if (column == 0)
			return _exam->name(); */
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
