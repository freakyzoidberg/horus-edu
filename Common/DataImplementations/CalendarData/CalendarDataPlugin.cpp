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
#include "CalendarDataPlugin.h"
#include "CalendarData.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

CalendarData* CalendarDataPlugin::getCalendar(TreeData* node)
{
        foreach (CalendarData* wb, whiteBoards)
		if (qobject_cast<TreeData *>(wb->node()) == node)
			return wb;

        CalendarData* wb = new CalendarData(node, this);
#ifdef HORUS_CLIENT
	wb->moveToThread(this->thread());
#endif
	whiteBoards.append(wb);
	return wb;
}

CalendarData* CalendarDataPlugin::getCalendar(quint32 nodeId)
{
        return getCalendar( pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId) );
}

Data* CalendarDataPlugin::getDataWithKey(QDataStream& s)
{
	quint32 nodeId;
	s >> nodeId;
        return getCalendar(nodeId);
}

QList<Data*> CalendarDataPlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, whiteBoards)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_SERVER
void CalendarDataPlugin::loadData()
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
                CalendarData* wb	= getCalendar(query.value(0).toUInt());
                wb->_syncMode		= (CalendarData::SyncMode)(query.value(1).toUInt());
		wb->_items			= query.value(2).toByteArray();
		wb->_lastChange		= query.value(3).toDateTime();
		wb->_status			= Data::UPTODATE;
	}
}

QList<Data*> CalendarDataPlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (CalendarData* data, whiteBoards)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
