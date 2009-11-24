#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardData.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

WhiteBoardDataPlugin::WhiteBoardDataPlugin()
{
}

WhiteBoardData* WhiteBoardDataPlugin::whiteBoard(TreeData* node)
{
	foreach (Data* d, _allDatas)
	{
		WhiteBoardData* wb = (WhiteBoardData*)d;
		if (wb->node() == node)
			return wb;
	}

	WhiteBoardData* wb = new WhiteBoardData(node, this);
	wb->moveToThread(thread());
	_allDatas.append(wb);
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

void WhiteBoardDataPlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id_tree`,`mode`,`items`,`mtime`FROM`white_board`;");
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
#endif
}

void WhiteBoardDataPlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (WhiteBoardData*)d;
	_allDatas.clear();
	DataPlugin::unload();
}

bool WhiteBoardDataPlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	if ( ! tree || ! tree->canLoad())
		return false;

#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS`white_board` (\
						`id_tree`int(11) NOT NULL,\
						`mode`int(1) NOT NULL,\
						`items`blob,\
						`mtime`timestamp NOT NULL,\
						PRIMARY KEY(`id_tree`)\
					);")
		||
		 ! query.exec("SELECT`id_tree`,`mode`,`items`,`mtime`FROM`white_board`WHERE`id_tree`=-1;")
		)
	{
		qDebug() << "WhiteBoardDataPlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}
