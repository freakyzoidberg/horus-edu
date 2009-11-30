#include "LibraryFilter.h"
#include "../../../Common/FileData.h"
#include <QItemSelection>
#include <QDebug>

LibraryFilter::LibraryFilter(QAbstractListModel* fileModel, QObject* parent) : QSortFilterProxyModel(parent)
{
	setSourceModel(fileModel);
	setSortCaseSensitivity(Qt::CaseInsensitive);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
	sort(0, Qt::AscendingOrder);
}

void LibraryFilter::treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected)
{
	foreach (QModelIndex index, selected.indexes())
		_nodes.append(static_cast<TreeData*>(index.internalPointer()));
	foreach (QModelIndex index, deselected.indexes())
		_nodes.removeOne(static_cast<TreeData*>(index.internalPointer()));

	invalidateFilter();
}

bool LibraryFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	if ( ! _nodes.contains(static_cast<FileData*>(sourceModel()->index(source_row, 0, source_parent).internalPointer())->node()))
		return false;

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
