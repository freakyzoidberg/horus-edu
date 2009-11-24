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
	return ((Data*)(index.internalPointer()))->data(index.column(), role);
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
