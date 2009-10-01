#include "WhiteBoardData.h"
#include "WhiteBoardDataPlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"

void WhiteBoardData::keyToStream(QDataStream& s)
{
	s << _node->id();
}

void WhiteBoardData::dataToStream(QDataStream& s) const
{
	s << _syncMode;
#ifdef HORUS_CLIENT
	QByteArray bufItems;
	QDataStream ds(&bufItems, QIODevice::WriteOnly);
	foreach (const WhiteBoardItem& item, _items)
		item >> ds;

	s << bufItems;
#endif
#ifdef HORUS_SERVER
	s << _items;
#endif

	Data::dataToStream(s);
}

void WhiteBoardData::dataFromStream(QDataStream& s)
{
	_items.clear();

	s >> _syncMode;

#ifdef HORUS_CLIENT
	QByteArray bufItems;
	s >> bufItems;
	QDataStream ds(bufItems);
	while ( ! ds.atEnd())
		_items.append( WhiteBoardItem(ds) );
#endif
#ifdef HORUS_SERVER
	s >> _items;
#endif

	Data::dataFromStream(s);
}

QDebug WhiteBoardData::operator<<(QDebug debug) const
{
	return debug << tr("WhiteBoardData::") << _node->id();
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant WhiteBoardData::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
			return ((TreeData*)parent())->id();
        if (column == 1)
			return tr("White Board");
    }
//    else if (role == Qt::DecorationRole && column == 0)
//    {
//        return QIcon(":/user.ico");
//    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
void WhiteBoardData::fillFromDatabase(QSqlQuery& query)
{
	query.prepare("SELECT mode,items,mtime FROM white_board WHERE id_tree=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.next())
		return createIntoDatabase(query);

	_syncMode	= (SyncMode)(query.value(0).toUInt());
	_items		= query.value(1).toByteArray();
	_lastChange	= query.value(2).toDateTime();
}

void WhiteBoardData::createIntoDatabase(QSqlQuery& query)
{
	query.prepare("INSERT INTO white_board (id_tree,mode,items,mtime)VALUES(?,?,?,?);");
	query.addBindValue(_node->id());
	query.addBindValue(_syncMode);
	query.addBindValue(_items);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
}

void WhiteBoardData::saveIntoDatabase(QSqlQuery& query)
{
	query.prepare("UPDATE white_board SET mode=?,items=?,mtime=? WHERE id_tree=?;");
	query.addBindValue(_syncMode);
	query.addBindValue(_items);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.numRowsAffected())
		_error = NOT_FOUND;
}

void WhiteBoardData::deleteFromDatabase(QSqlQuery& query)
{
	query.prepare("DELETE FROM white_board WHERE id_tree=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.numRowsAffected())
		_error = NOT_FOUND;
}
#endif
