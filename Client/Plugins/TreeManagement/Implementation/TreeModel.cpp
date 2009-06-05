#include "TreeModel.h"
#include "Tree.h"

#include <QDebug>

int TreeModel::columnCount ( const QModelIndex & parent ) const
{
    return 1;
}

QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

    return QVariant(((Tree*)(index.internalPointer()))->GetName());
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    Tree* node;
    if (parent.isValid())
        node = (Tree*)(parent.internalPointer());
    else
        node = Tree::GetNodebyId(0);

    if ( ! node->GetSonsNode().count())
        return QModelIndex();

    qDebug() << "index" << node->Getid() << node->GetSonsNode().count() << row << column;

    return createIndex(row, 0, node->GetSonsNode().at(row));
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();
//        return createIndex(0, 0, Tree::GetNodebyId(0));

    Tree* p = ((Tree*)(index.internalPointer()))->GetParent();
    if (p->Getid() == 0)
        return QModelIndex();

    qDebug() << "parent" << p->Getid() << p->GetSonsNode().count();

    return createIndex(p->GetParent()->GetSonsNode().indexOf(p), 0, p);
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    Tree* p;

    if ( ! parent.isValid())
        p = Tree::GetNodebyId(0);
    else
        p = ((Tree*)(parent.internalPointer()));

    qDebug() << "rowCount" << p->Getid() << p->GetSonsNode().count();

    return p->GetSonsNode().count();
}
