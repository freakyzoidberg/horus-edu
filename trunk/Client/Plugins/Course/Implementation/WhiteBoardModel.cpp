#include "WhiteBoardModel.h"

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"

WhiteBoardModel::WhiteBoardModel(PluginManager* _pluginManager)
{
    pluginManager = _pluginManager;
    rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0));
}

int WhiteBoardModel::columnCount ( const QModelIndex & ) const
{
    return (1);
}

int WhiteBoardModel::rowCount ( const QModelIndex & parent ) const
{
	// if invalid, parent is the parent of the rootElement, so only the rootElement in child
	if (!parent.isValid())
		return (1);
	// if parent is not a TreeData*, it's a WhiteBoardData, so there's no child
	TreeData* node = qobject_cast<TreeData*>((Data*)(parent.internalPointer()));
	if (!node)
		return (0);
	// look if there is a WhiteBoard inside
	if (qobject_cast<WhiteBoardData *>(pluginManager->findPlugin<WhiteBoardDataPlugin *>()->getWhiteBoard(node))->status() != Data::EMPTY)
		return (node->children().count() + 1);
	return (node->children().count());
}

//QVariant WhiteBoardModel::headerData (int section, Qt::Orientation orientation, int role) const
//{
//   if (role == Qt::DisplayRole)
//        return QVariant("");
//   return QVariant();
//}

QVariant WhiteBoardModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
        return (QVariant());
    if (role == Qt::DisplayRole)
	{
		TreeData* node = qobject_cast<TreeData*>((Data*)(index.internalPointer()));
		if (node || index.column() != 1)
			return ((Data*)(index.internalPointer()))->data(index.column() + 1, role);
		return ("WHITEBOARD");
	}
    return ((Data*)(index.internalPointer()))->data(index.column(), role);
}

QModelIndex WhiteBoardModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if (!parent.isValid())
        return (createIndex(row, column, rootItem));
	TreeData* node = qobject_cast<TreeData*>((Data*)(parent.internalPointer()));
	if (node->children().count() > row)
		return (createIndex(row, column, node->children().at(row)));
	return (createIndex(row, column, pluginManager->findPlugin<WhiteBoardDataPlugin *>()->getWhiteBoard(node)));
}

QModelIndex WhiteBoardModel::parent ( const QModelIndex & index ) const
{
	//should not happen
	if (!index.isValid())
		return (QModelIndex());
	TreeData* node = qobject_cast<TreeData*>((Data*)(index.internalPointer()));
	// if index is a node
	if (node)
	{
		//if index is the rootElement
		if (node == rootItem)
			return (QModelIndex());
		// the node is the parent
		node = (TreeData* )(node->parent());
	}
	else
		node = ((WhiteBoardData *)(index.internalPointer()))->node();
	// if the parent is the root item
	if (node == rootItem)
            return (createIndex(0, 0, rootItem));
	return (createIndex(node->parent()->children().indexOf(node), 0, node));
}
