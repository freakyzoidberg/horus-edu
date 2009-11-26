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
#include "WhiteBoardModel.h"

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"

WhiteBoardModel::WhiteBoardModel(PluginManager* _pluginManager)
{
    pluginManager = _pluginManager;
	rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->rootNode());
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
	if (qobject_cast<WhiteBoardData *>(pluginManager->findPlugin<WhiteBoardDataPlugin *>()->whiteBoard(node))->status() != Data::EMPTY)
		return (node->children().count() + 1);
	return (node->children().count());
}

QVariant WhiteBoardModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
        return (QVariant());
    if (role == Qt::BackgroundRole)
        return QVariant();
    if (role == Qt::DisplayRole)
	{
		TreeData* node = qobject_cast<TreeData*>((Data*)(index.internalPointer()));
		if (node || index.column() != 1)
			return ((Data*)(index.internalPointer()))->data(index.column(), role);
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
	return (createIndex(row, column, pluginManager->findPlugin<WhiteBoardDataPlugin *>()->whiteBoard(node)));
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

//bool		WhiteBoardModel::insertRow(WhiteBoardData *wbd)
//{
//	TreeData *parent = wbd->node();
//	TreeData *gparent = parent->parent();
//	QModelIndex parentIndex = createdIndex(gparent->children().indexOf(parent), 0, parent);
//	this->beginInsertRows(parentIndex, 0, 1);
//}
