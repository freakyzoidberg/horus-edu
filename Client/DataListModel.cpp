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
#include "DataListModel.h"
#include "../Common/Data.h"

DataListModel::DataListModel(const DataPlugin* plugin)
{
	_plugin = plugin;
	foreach (Data* d, _plugin->allDatas())
		if IS_VALID_DATA_STATUS(d->status())
			_list.append(d);
	//DirectConnexion because a REMOVED data is deleted after the signal
	 connect(_plugin, SIGNAL(dataStatusChanged(Data*)), this, SLOT(dataStatusChanged(Data*)), Qt::DirectConnection);
	 setSupportedDragActions(Qt::MoveAction);
}

QModelIndex DataListModel::index(int row, int column, const QModelIndex &) const
{
	return createIndex(row, column, _list.at(row));
}

int DataListModel::rowCount(const QModelIndex &) const
{
	return _list.count();
}

QVariant DataListModel::data(const QModelIndex &index, int role) const
{
	return static_cast<Data*>(index.internalPointer())->data(index.column(), role);
}

void DataListModel::dataStatusChanged(Data* data)
{
	if IS_VALID_DATA_STATUS(data->status())
	{
		if ( ! _list.contains(data))
		{
			int pos = _list.count();
			beginInsertRows(QModelIndex(), pos, pos);
			_list.append(data);
			endInsertRows();
		}
//		else
//		{
//			QModelIndex i = index(_list.indexOf(data), 0, QModelIndex());
//			changePersistentIndex(i, i);
//		}
	}
	else
	{
		if (_list.contains(data))
		{
			int pos = _list.indexOf(data);
			beginRemoveRows(QModelIndex(), pos, pos);
			_list.removeOne(data);
			endRemoveRows();
		}
	}
}

Qt::DropActions DataListModel::supportedDropActions() const
{
	return Qt::MoveAction;
}

QMimeData* DataListModel::mimeData(const QModelIndexList &indexes) const
{
	return static_cast<Data*>(indexes.first().internalPointer())->mimeData();
}


Qt::ItemFlags DataListModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QAbstractListModel::flags(index);
	else
		return Qt::ItemIsDropEnabled | QAbstractListModel::flags(index);
}

bool DataListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	return static_cast<Data*>(index(row, column, parent).internalPointer())->dropMimeData(data, action);
}
