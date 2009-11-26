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
#include "GradeDataBase.h"
#include "GradeDataBasePlugin.h"

#include "../../TreeData.h"

GradeDataBase::GradeDataBase(TreeData* node, GradeDataBasePlugin* plugin) : GradeData(plugin)
{

}

void GradeDataBase::keyToStream(QDataStream& s)
{

}

void GradeDataBase::dataToStream(QDataStream& s) const
{

}

void GradeDataBase::dataFromStream(QDataStream& s)
{

}

QDebug GradeDataBase::operator<<(QDebug debug) const
{

}

#ifdef HORUS_SERVER
quint8 GradeDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT start_time,end_time FROM event WHERE id_tree=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_startTime = query.value(0).toDateTime();
	_endTime   = query.value(1).toDateTime();

	return NONE;
}

quint8 GradeDataBase::serverCreate()
{
	QMutexLocker M(&_node->mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO event (id_tree,start_time,end_time) VALUES (?,?,?);");
	query.addBindValue(_node->id());
	query.addBindValue(_startTime);
	query.addBindValue(_endTime);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	return NONE;
}

quint8 GradeDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE event SET start_time=?,end_time=? WHERE id_tree=?;");
	query.addBindValue(_startTime);
	query.addBindValue(_endTime);
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

quint8 GradeDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM event WHERE id_tree=?;");
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
//void GradeDataBase::create()
//{
//	disconnect(this, SLOT(create()));
//	if (_node->status() == CREATING || _node->status() == EMPTY)
//		connect(_node, SIGNAL(created()), this, SLOT(create()));
//	else
//		Data::create();
//}
//
//
////#include <QIcon>
//QVariant GradeDataBase::data(int column, int role) const
//{
//    if (role == Qt::DisplayRole)
//    {
//        if (column == 0)
//			return _node->id();
//        if (column == 1)
//			return _node->name();
//        if (column == 2)
//			return _startTime;
//		if (column == 3)
//			return _endTime;
//    }
////    else if (role == Qt::DecorationRole && column == 0)
////    {
////        static QMap<QString,QIcon> icons;
////        if ( ! icons.count())
////        {
////            icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
////			icons["LESSON"]  = QIcon(":/Icons/LessonIcon.png");
////            icons["SUBJECT"] = QIcon(":/Icons/SubjectIcon.png");
////			icons["GRADE"]   = QIcon(":/Icons/GradeIcon.png");
////			icons["GROUP"]   = QIcon(":/Icons/GroupIcon.png");
////			icons["ROOT"]    = QIcon(":/Icons/RootIcon.png");
////        }
////        if (icons.contains( _type ))
////            return icons[ _type ];
////        return icons["DEFAULT"];
////    }
//   return Data::data(column, role);
//}
#endif
