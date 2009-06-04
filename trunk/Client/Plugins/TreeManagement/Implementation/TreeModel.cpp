#include "TreeModel.h"
#include "Tree.h"

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 4;
}

QVariant TreeModel::data ( const QModelIndex & index, int ) const
{
    return ((Tree*)index.internalPointer())->GetName();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & ) const
{
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
}

int TreeModel::rowCount ( const QModelIndex & ) const
{
    return Tree::countNodes();
}
