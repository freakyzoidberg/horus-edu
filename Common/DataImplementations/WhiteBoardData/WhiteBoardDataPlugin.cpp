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
