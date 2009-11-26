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
#include "CalendarData.h"
#include "CalendarDataPlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"

void CalendarData::keyToStream(QDataStream& s)
{
	s << _node->id();
}

void CalendarData::dataToStream(QDataStream& s) const
{
	s << _syncMode;
#ifdef HORUS_CLIENT
	QByteArray bufItems;
	QDataStream ds(&bufItems, QIODevice::WriteOnly);
        foreach (const CalendarItem& item, _items)
		item >> ds;

	s << bufItems;
#endif
#ifdef HORUS_SERVER
	s << _items;
#endif

	Data::dataToStream(s);
}

void CalendarData::dataFromStream(QDataStream& s)
{
	_items.clear();

	s >> _syncMode;

#ifdef HORUS_CLIENT
	QByteArray bufItems;
	s >> bufItems;
	QDataStream ds(bufItems);
	_items.clear();
	while ( ! ds.atEnd())
                _items.append( CalendarItem(ds) );
#endif
#ifdef HORUS_SERVER
	s >> _items;
#endif

	Data::dataFromStream(s);
}

QDebug CalendarData::operator<<(QDebug debug) const
{
        return debug << tr("CalendarData::") << _node->id();
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant CalendarData::data(int column, int role) const
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
quint8 CalendarData::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT mode,items,mtime FROM white_board WHERE id_tree=?;");
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

quint8 CalendarData::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO white_board (id_tree,mode,items,mtime)VALUES(?,?,?,?);");
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

quint8 CalendarData::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE white_board SET mode=?,items=?,mtime=? WHERE id_tree=?;");
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

quint8 CalendarData::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM white_board WHERE id_tree=?;");
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
