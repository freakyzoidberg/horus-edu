#include "EventDataBase.h"
#include "EventDataBasePlugin.h"

#include "../../TreeData.h"

EventDataBase::EventDataBase(TreeData* node, EventDataBasePlugin* plugin) : EventData(plugin)
{
	_node = node;
	_node->registerData(this);
}

void EventDataBase::keyToStream(QDataStream& s)
{
	s << _node->id();
}

void EventDataBase::dataToStream(QDataStream& s) const
{
	s << _startTime << _endTime;
}

void EventDataBase::dataFromStream(QDataStream& s)
{
	s >> _startTime >> _endTime;
}

QDebug EventDataBase::operator<<(QDebug debug) const
{
	return debug << dataType() << _node->id() << _startTime << _endTime;
}

#ifdef HORUS_SERVER
quint8 EventDataBase::serverRead()
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

quint8 EventDataBase::serverCreate()
{
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

quint8 EventDataBase::serverSave()
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
		return serverCreate();

	return NONE;
}

quint8 EventDataBase::serverRemove()
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
//#include <QIcon>
QVariant EventDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
			return _node->id();
        if (column == 1)
			return _node->name();
        if (column == 2)
			return _startTime;
		if (column == 3)
			return _endTime;
    }
//    else if (role == Qt::DecorationRole && column == 0)
//    {
//        static QMap<QString,QIcon> icons;
//        if ( ! icons.count())
//        {
//            icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
//			icons["LESSON"]  = QIcon(":/Icons/LessonIcon.png");
//            icons["SUBJECT"] = QIcon(":/Icons/SubjectIcon.png");
//			icons["GRADE"]   = QIcon(":/Icons/GradeIcon.png");
//			icons["GROUP"]   = QIcon(":/Icons/GroupIcon.png");
//			icons["ROOT"]    = QIcon(":/Icons/RootIcon.png");
//        }
//        if (icons.contains( _type ))
//            return icons[ _type ];
//        return icons["DEFAULT"];
//    }
   return Data::data(column, role);
}
#endif
