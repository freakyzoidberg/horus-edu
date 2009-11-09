#include "LibraryModel.h"

#include "../../../Common/FileData.h"

int LibraryModel::rowCount(const QModelIndex&) const
{
	return _plugin->allFiles().count();
}

QModelIndex LibraryModel::index(int row, int col, const QModelIndex&) const
{
	return createIndex(row, col, (_plugin->allFiles().begin() + row).value());
}

QVariant LibraryModel::data(const QModelIndex& index, int role) const
{
	return ((FileData*)(index.internalPointer()))->data(index.column(), role);
}

#include "../../../Common/TreeData.h"

int TreeModel::rowCount(const QModelIndex& index) const
{
	if ( ! index.isValid())
		return 1;

	return ((TreeData*)(index.internalPointer()))->children().count();
}

int TreeModel::columnCount(const QModelIndex&) const
{
	return 1;
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
	TreeData* node = ((TreeData*)(child.internalPointer()));

	if (node == _plugin->rootNode())
		return QModelIndex();

	node = node->parent();
	int row = 0;
	if (node != _plugin->rootNode())
		row = node->parent()->children().indexOf(node);

	return createIndex(row, 0, node);
}

QModelIndex TreeModel::index(int row, int col, const QModelIndex& parent) const
{
	if ( ! parent.isValid())
		return createIndex(0, 0, _plugin->rootNode());

	TreeData* node = ((TreeData*)(parent.internalPointer()));

	return createIndex(row, col, node->children().at(row));
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
	return ((FileData*)(index.internalPointer()))->data(index.column(), role);
}
