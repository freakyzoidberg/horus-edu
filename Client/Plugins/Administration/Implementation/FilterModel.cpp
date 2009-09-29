#include "FilterModel.h"

FilterModel::FilterModel(int _type, QObject *parent)
{
    type = _type;
}


QModelIndex FilterModel::index(int row, int column, const QModelIndex &parent) const
{
    return mapFromSource(sourceModel()->index(row, column, parent));
}

QModelIndex FilterModel::parent(const QModelIndex &index) const
{
    return sourceModel()->parent(index);
}

QModelIndex FilterModel::mapToSource(const QModelIndex &proxyIndex) const
{
    return sourceModel()->index(proxyIndex.row(), proxyIndex.column(), proxyIndex.parent());
}

QModelIndex FilterModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return createIndex(sourceIndex.row(), sourceIndex.column(), sourceIndex.internalPointer());
}

int FilterModel::rowCount(const QModelIndex &index) const
{
    return sourceModel()->rowCount(index);
}

int FilterModel::columnCount(const QModelIndex &index) const
{
    return sourceModel()->columnCount(index);
}
