#include "TreeModel.h"
#include "../../../Common/TreeData.h"

TreeModel::TreeModel(const TreeDataPlugin* plugin)
{
	_plugin = plugin;
	foreach (Data* d, _plugin->allDatas())
		if IS_VALID_DATA_STATUS(d->status())
		{
			TreeData* node = static_cast<TreeData*>(d);
			_data.insertMulti(node->parent(), node);
		}
	//DirectConnexion because a REMOVED data is deleted just after the signal
	 connect(_plugin, SIGNAL(dataStatusChanged(Data*)), this, SLOT(dataStatusChanged(Data*)), Qt::QueuedConnection);
}

int TreeModel::rowCount(const QModelIndex & parent) const
{
	if ( ! parent.isValid())
		return 1;

	return _data.count(static_cast<TreeData*>(parent.internalPointer()));
}

int TreeModel::columnCount(const QModelIndex &) const
{
	return 1;
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
	Data* data = static_cast<Data*>(child.internalPointer());
	if (data == _plugin->rootNode())
		return QModelIndex();

	TreeData* node = _data.key(data);
	if (node == _plugin->rootNode())
		return createIndex(0, 0, node);

	return createIndex(_data.values(_data.key(node)).indexOf(node), 0, node);
}

QModelIndex TreeModel::index(int row, int, const QModelIndex & parent) const
{
	if ( ! parent.isValid())
		return createIndex(0, 0, _plugin->rootNode());

	return createIndex(row, 0, _data.values(static_cast<TreeData*>(parent.internalPointer())).at(row));
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	return (static_cast<Data*>(index.internalPointer()))->data(index.column(), role);
}

void TreeModel::dataStatusChanged(Data* data)
{
	TreeData* parent = _data.key(data);

	//if a data is removed
	if ( ! IS_VALID_DATA_STATUS(data->status()))
	{
		if (parent)
			removeData(parent, data);
		return;
	}

	if (parent)
		//if the parent has change
		if (parent != (static_cast<TreeData*>(data))->parent())
			removeData(parent, data);

	parent = (static_cast<TreeData*>(data))->parent();

	//if the node is not in the model
	if ( ! _data.contains(parent, data))
		inserData(parent, data);

//		else
//		{
//			QModelIndex i = index(_list.indexOf(data), 0, QModelIndex());
//			changePersistentIndex(i, i);
//		}
}

void TreeModel::inserData(TreeData* parentNode, Data* data)
{
	int pos = _data.count(parentNode);
	int row = 1;
	if (parentNode != _plugin->rootNode())
		row = _data.values(_data.key(parentNode)).indexOf(parentNode);

	beginInsertRows(createIndex(row, 0, data), pos, pos);
	_data.insertMulti(parentNode, data);
	endInsertRows();
}

void TreeModel::removeData(TreeData* parentNode, Data* data)
{
	int pos = _data.values(parentNode).indexOf(data);
	beginRemoveRows(parent(createIndex(pos, 0, data)), pos, pos);
	_data.remove(parentNode, data);
	endRemoveRows();
}
