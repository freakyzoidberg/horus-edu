#include "TreeModel.h"
#include "Tree.h"

#include <QDebug>

int TreeModel::columnCount ( const QModelIndex & parent ) const
{
    return 1;
}

QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if ( ! index.isValid())
        return QVariant();

    qDebug() << ((Tree*)(index.internalPointer()))->GetName();
    return QVariant(((Tree*)(index.internalPointer()))->GetName());
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, Tree::GetNodebyId(0));

    Tree* node = (Tree*)(parent.internalPointer());
    if ( ! node->GetSonsNode().count())
        return QModelIndex();

//    qDebug() << "index" << node->Getid() << node->GetSonsNode().count() << row << column << node->GetSonsNode().at(row)->GetName();

    return createIndex(row, column, node->GetSonsNode().at(row));
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();

    Tree* i = ((Tree*)(index.internalPointer()));
    if (i->Getid() == 0)
        return QModelIndex();

    i = i->GetParent();

//    qDebug() << "parent" << p->Getid() << p->GetSonsNode().count();

    return createIndex(i->GetParent()->GetSonsNode().indexOf(i), 0, i);
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;

    return ((Tree*)(parent.internalPointer()))->GetSonsNode().count();
}
