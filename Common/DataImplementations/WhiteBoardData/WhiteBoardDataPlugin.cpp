#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardData.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

WhiteBoardData* WhiteBoardDataPlugin::getWhiteBoard(TreeData* node)
{
	foreach (WhiteBoardData* wb, whiteBoards)
		if (qobject_cast<TreeData *>(wb->node()) == node)
			return wb;

	WhiteBoardData* wb = new WhiteBoardData(node, this);
#ifdef HORUS_CLIENT
	wb->moveToThread(this->thread());
#endif
	whiteBoards.append(wb);
	return wb;
}

WhiteBoardData* WhiteBoardDataPlugin::getWhiteBoard(quint32 nodeId)
{
	return getWhiteBoard( pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId) );
}

Data* WhiteBoardDataPlugin::getDataWithKey(QDataStream& s)
{
	quint32 nodeId;
	s >> nodeId;
	return getWhiteBoard(nodeId);
}

#ifdef HORUS_SERVER
void WhiteBoardDataPlugin::loadDataBase(QSqlQuery& query)
{
	query.prepare("SELECT id_tree,mode,items,mtime FROM white_board;");
	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	while (query.next())
	{
		WhiteBoardData* wb	= getWhiteBoard(query.value(0).toUInt());
		wb->_syncMode		= (WhiteBoardData::SyncMode)(query.value(1).toUInt());
		wb->_items			= query.value(2).toByteArray();
		wb->_lastChange		= query.value(3).toDateTime();
		wb->_status			= Data::UPTODATE;
	}
}

void WhiteBoardDataPlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
	foreach (WhiteBoardData* data, whiteBoards)
		if (data->lastChange() >= date)
			dataManager->sendData(user, data);
}
#endif
