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
	sort(0, Qt::AscendingOrder);
}

void LibraryFilterProxyModel::nodeListChanged(const QList<Data*>& list)
{
	_nodes = list;
	invalidateFilter();
}

bool LibraryFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	if ( ! _nodes.contains(static_cast<FileData*>(sourceModel()->index(source_row, 0, source_parent).internalPointer())->node()))
		return false;

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
