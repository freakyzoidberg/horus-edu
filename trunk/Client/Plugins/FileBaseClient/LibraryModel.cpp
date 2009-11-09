#include "LibraryModel.h"
#include "../../../Common/FileData.h"
#include "../../../Common/PluginManager.h"

LibraryModel::LibraryModel(PluginManager* pluginManager)
{
	_plugin = pluginManager->findPlugin<FileDataPlugin*>();
}

int LibraryModel::rowCount(const QModelIndex& index) const
{
	return _plugin->getAllFiles().count();
}

QModelIndex LibraryModel::index(int row, int col, const QModelIndex& parent) const
{
	return createIndex(row, col, (_plugin->getAllFiles().begin() + row).value());
}

QVariant LibraryModel::data(const QModelIndex& index, int role) const
{
	return ((FileData*)(index.internalPointer()))->data(index.column(), role);
}
