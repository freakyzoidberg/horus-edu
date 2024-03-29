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
#include "ExamsDataBase.h"
#include "ExamsDataBasePlugin.h"

#include "../../TreeData.h"
#include "../../UserData.h"

ExamsDataBase::ExamsDataBase(quint32 id, ExamsDataBasePlugin* plugin) : ExamsData(id, plugin)
{
	moveToThread(plugin->thread());
}

void ExamsDataBase::keyToStream(QDataStream& s) const
{
	s << _id;
}

void ExamsDataBase::dataToStream(QDataStream& s) const
{
	s << _comment << _date << _teacher << _subject->id();
}

void ExamsDataBase::dataFromStream(QDataStream& s)
{
	quint32	subjectId;

	s >> _comment >> _date >> _teacher >> subjectId;

	setSubject(_plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(subjectId));
}

bool ExamsDataBase::canChange(UserData* user) const
{
		return true;
}

bool ExamsDataBase::canAccess(UserData* user) const
{
	return true;
}

QDebug ExamsDataBase::operator<<(QDebug debug) const
{
	return debug << dataType() << _subject->id() << _comment << _teacher;
}

const QList<Data*> ExamsDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_subject);
	return list;
}

#ifdef HORUS_SERVER
quint8 ExamsDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`comment`,`date`,`teacher_id`,`id_tree`FROM`Exams`WHERE id=?");
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_comment	= query.value(0).toString();
	_date		= query.value(1).toDate();
	_teacher	= query.value(2).toInt();
	this->_subject =
	_plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(3).toUInt());
	return NONE;
}

quint8 ExamsDataBase::serverCreate()
{
	QMutexLocker M(&_subject->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`Exams`(`id_tree`,`comment`,`date`,`teacher_id`)VALUES(?,?,?, ?);");
	query.addBindValue(_subject->id());
	query.addBindValue(_comment);
	query.addBindValue(_date);
	query.addBindValue(_teacher);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	_id = query.lastInsertId().toUInt();
	return NONE;
}

quint8 ExamsDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`Exams`SET`comment`=?,`date`=?,`teacher_id`=? WHERE`id_tree`=?;");
	query.addBindValue(_comment);
	query.addBindValue(_date);
	query.addBindValue(_teacher);
	query.addBindValue(_subject->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 ExamsDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`Exams`WHERE`id_tree`=?;");
	query.addBindValue(_subject->id());

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
QVariant ExamsDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
		if (column == 0)
			return _id;
		if (column == 1)
			return _comment;
		if (column == 2)
			return _date;
		if (column == 3)
			return _teacher;
		if (column == 4)
			return _subject->id();
	}
   return Data::data(column, role);
}
#endif
