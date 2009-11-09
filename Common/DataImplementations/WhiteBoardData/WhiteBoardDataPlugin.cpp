#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardData.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

WhiteBoardData* WhiteBoardDataPlugin::whiteBoard(TreeData* node)
{
	foreach (WhiteBoardData* wb, _whiteBoards)
		if (qobject_cast<TreeData *>(wb->node()) == node)
			return wb;

	WhiteBoardData* wb = new WhiteBoardData(node, this);
#ifdef HORUS_CLIENT
	wb->moveToThread(this->thread());
#endif
	_whiteBoards.append(wb);
	return wb;
}

WhiteBoardData* WhiteBoardDataPlugin::whiteBoard(quint32 nodeId)
{
	return whiteBoard( pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId) );
}

Data* WhiteBoardDataPlugin::dataWithKey(QDataStream& s)
{
	quint32 nodeId;
	s >> nodeId;
	return whiteBoard(nodeId);
}

QList<Data*> WhiteBoardDataPlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, _whiteBoards)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_SERVER
void WhiteBoardDataPlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id_tree,mode,items,mtime FROM white_board;");
	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	while (query.next())
	{
		WhiteBoardData* wb	= whiteBoard(query.value(0).toUInt());
		wb->_syncMode		= (WhiteBoardData::SyncMode)(query.value(1).toUInt());
		wb->_items			= query.value(2).toByteArray();
		wb->_lastChange		= query.value(3).toDateTime();
		wb->_status			= Data::UPTODATE;
	}
}

QList<Data*> WhiteBoardDataPlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (WhiteBoardData* data, _whiteBoards)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
