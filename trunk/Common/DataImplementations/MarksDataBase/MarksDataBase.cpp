#include "MarksDataBase.h"
#include "MarksDataBasePlugin.h"

#include "../../TreeData.h"

MarksDataBase::MarksDataBase(MarksDataBasePlugin* plugin) : MarksData(plugin)
{

}

void MarksDataBase::keyToStream(QDataStream& s)
{

}

void MarksDataBase::dataToStream(QDataStream& s) const
{

}

void MarksDataBase::dataFromStream(QDataStream& s)
{

}

QDebug MarksDataBase::operator<<(QDebug debug) const
{

}

#ifdef HORUS_SERVER
quint8 MarksDataBase::serverRead()
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

quint8 MarksDataBase::serverCreate()
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

quint8 MarksDataBase::serverSave()
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

quint8 MarksDataBase::serverRemove()
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
void MarksDataBase::create()
{
	disconnect(this, SLOT(create()));
	if (_node->status() == CREATING || _node->status() == EMPTY)
		connect(_node, SIGNAL(created()), this, SLOT(create()));
	else
		Data::create();
}


//#include <QIcon>
QVariant MarksDataBase::data(int column, int role) const
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

   return Data::data(column, role);
}
#endif
