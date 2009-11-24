#include "WhiteBoardData.h"
#include "WhiteBoardDataPlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"
#include "../../UserData.h"

WhiteBoardData::WhiteBoardData(TreeData* node, WhiteBoardDataPlugin* plugin) : Data(plugin)
{
	_node = node;
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
}

void WhiteBoardData::keyToStream(QDataStream& s) const
{
	s << _node->id();
}

void WhiteBoardData::dataToStream(QDataStream& s) const
{
	s << (quint8)_syncMode;
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

	quint8 sm;
	s >> sm;
	_syncMode = (SyncMode)sm;

#ifdef HORUS_CLIENT
	QByteArray bufItems;
	s >> bufItems;
	QDataStream ds(bufItems);
	_items.clear();
	while ( ! ds.atEnd())
		_items.append( WhiteBoardItem(ds) );
#endif
#ifdef HORUS_SERVER
	s >> _items;
#endif

	Data::dataFromStream(s);
}

bool WhiteBoardData::canChange(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR)
		return true;
	return _node->canChange(user);
}

bool WhiteBoardData::canAccess(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR)
		return true;
	return _node->canAccess(user);
}

QDebug WhiteBoardData::operator<<(QDebug debug) const
{
	return debug << tr("WhiteBoardData::") << _node->id();
}

const QList<Data*> WhiteBoardData::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_node);
	return list;
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant WhiteBoardData::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
		if (column == -1)
			return _node->id();
		if (column == 0)
                        return tr("Class");
    }
//    else if (role == Qt::DecorationRole && column == 0)
//    {
//        return QIcon(":/user.ico");
//    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
quint8 WhiteBoardData::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`mode`,`items`,`mtime`FROM`white_board`WHERE`id_tree`=?;");
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return serverCreate();

	_syncMode	= (SyncMode)(query.value(0).toUInt());
	_items		= query.value(1).toByteArray();
	_lastChange	= query.value(2).toDateTime();
	return NONE;
}

quint8 WhiteBoardData::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`white_board`(`id_tree`,`mode`,`items`,`mtime`)VALUES(?,?,?,?);");
	query.addBindValue(_node->id());
	query.addBindValue(_syncMode);
	query.addBindValue(_items);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 WhiteBoardData::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`white_board`SET`mode`=?,`items`=?,`mtime`=? WHERE`id_tree`=?;");
	query.addBindValue(_syncMode);
	query.addBindValue(_items);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
	query.addBindValue(_node->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 WhiteBoardData::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`white_board`WHERE`id_tree`=?;");
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
