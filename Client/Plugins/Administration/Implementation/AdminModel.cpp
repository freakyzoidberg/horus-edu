#include "AdminModel.h"

AdminModel::AdminModel(const QHash<quint32, UserData*>&  _users, TreeData *Data) : users(_users)
{
    rootItem = Data;
}

int AdminModel::columnCount ( const QModelIndex & ) const
{
    return 1;
}

int AdminModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;
//    Data *tmp = ((Data*)(parent.internalPointer()));
//
      TreeData* tmp = static_cast<TreeData*>(parent.internalPointer());
//    if (tmp2 == 0)
//        return tmp->children().count();
    int i = 0;
    foreach (UserData* user, users)
        if (user->node()->id() == tmp->id() && user->level() > 1)
            i++;
    return ((Data*)(parent.internalPointer()))->children().count() + i;
}

QVariant AdminModel::headerData (int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole)
        return QVariant("Administration Tree");
   return QVariant();
}

QVariant AdminModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        return ((Data*)(index.internalPointer()))->data(index.column() + 1, role);
    else
        return ((Data*)(index.internalPointer()))->data(index.column(), role);
}

QModelIndex AdminModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column + 1, rootItem);
    int i = 0;
    foreach (UserData* user, users)
    {
        if (user->node()->id() == ((TreeData*)(parent.internalPointer()))->id() && user->level() > 1)
        {
            if (i == row)
                return createIndex(row, column, user);
            i++;
        }
    }
    return createIndex(row, column, ((Data*)(parent.internalPointer()))->children().at(row - i) );
}

QModelIndex AdminModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if (obj == rootItem)
        return QModelIndex();

    if (obj->parent() == rootItem)
        return createIndex(0, 0, rootItem);

    obj = obj->parent();
    if (obj == 0)
    {
        UserData* tmp = (UserData*)(index.internalPointer());
        if (tmp != 0)
            return createIndex(0,0, tmp->node());
    }
    else
        return createIndex(obj->parent()->children().indexOf(obj), 0, obj);
}
