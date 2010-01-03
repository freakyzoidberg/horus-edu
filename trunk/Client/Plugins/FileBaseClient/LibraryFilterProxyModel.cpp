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
#include "LibraryFilterProxyModel.h"
#include "../../../Common/FileData.h"
#include "../../../Common/TreeData.h"
#include <QItemSelection>
#include <QDebug>

LibraryFilterProxyModel::LibraryFilterProxyModel(QAbstractListModel* fileModel, QObject* parent) : QSortFilterProxyModel(parent)
{
	setSourceModel(fileModel);
	setSortCaseSensitivity(Qt::CaseInsensitive);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
	setFilterRole(Data::FILTER_ROLE);
	setFilterKeyColumn(0);
	sort(0, Qt::AscendingOrder);
}

void LibraryFilterProxyModel::nodeListChanged(const QList<Data*>& list)
{
	_nodes = list;
	invalidateFilter();
}

void LibraryFilterProxyModel::filterUser(UserData* user)
{
	_user = user;
	invalidateFilter();
}

bool LibraryFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	FileData* file = static_cast<FileData*>(sourceModel()->index(source_row, 0, source_parent).internalPointer());

	if ( ! _nodes.contains(file->node()))
		return false;

	if (_user && file->owner() != _user)
		return false;

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
