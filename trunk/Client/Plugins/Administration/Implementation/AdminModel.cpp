#include "AdminModel.h"

AdminModel::AdminModel(const QHash<quint32, UserData*>&  _users, TreeData *Data)
{
    rootItem = Data;
}

int AdminModel::columnCount ( const QModelIndex & ) const
{
    return 3;
}

int AdminModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;

    return ((TreeData*)(parent.internalPointer()))->children().count();
}

//QVariant AdminModel::headerData (int section, Qt::Orientation orientation, int role) const
//{
//   if (role == Qt::DisplayRole)
//        return QVariant("");
//   return QVariant();
//}

QVariant AdminModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

    return ((TreeData*)(index.internalPointer()))->data(index.column(), role);
}

QModelIndex AdminModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, rootItem);

    return createIndex(row, column, ((TreeData*)(parent.internalPointer()))->children().at(row) );
}

QModelIndex AdminModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if (obj == rootItem)
        return QModelIndex();

    if (obj->parent() == rootItem)
        return createIndex(0, 0, rootItem);

    obj = obj->parent();
    return createIndex(obj->parent()->children().indexOf(obj), 0, obj);
}

