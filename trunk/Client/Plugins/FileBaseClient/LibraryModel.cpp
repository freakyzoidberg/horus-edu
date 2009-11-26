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
#include "LibraryModel.h"

#include <QIcon>
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
	if (role == Qt::DisplayRole)
		return ((FileData*)(index.internalPointer()))->data(index.column(), Qt::DisplayRole);
	if (role == Qt::DecorationRole)
		return QIcon(":/Icons/inode-directory.png");
	return QVariant();
}

bool LibrarySortFilter::filterAcceptsRow(int row, const QModelIndex& parent) const
{
//	((FileData*)(sourceModel()->index(row, 0, parent).internalPointer()));
//	if ()

	return QSortFilterProxyModel::filterAcceptsRow(row, parent);
}
