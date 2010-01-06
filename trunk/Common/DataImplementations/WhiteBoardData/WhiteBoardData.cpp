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
