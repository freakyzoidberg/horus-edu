#include "TreeModel.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"

TreeModel::TreeModel(PluginManager* _pluginManager)
{
    pluginManager = _pluginManager;
    rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0));
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 3;
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;
    return ((Data*)(parent.internalPointer()))->children().count();
}

//QVariant TreeModel::headerData (int section, Qt::Orientation orientation, int role) const
//{
//   if (role == Qt::DisplayRole)
//        return QVariant("");
//   return QVariant();
//}

QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

   return ((Data*)(index.internalPointer()))->data(index.column(), role);
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, rootItem);

    return createIndex(row, column, ((Data*)(parent.internalPointer()))->children().at(row) );
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if ( ! index.isValid() || obj == rootItem)
        return QModelIndex();

    int row = 0;
    if (obj->parent() != rootItem)
        row = obj->parent()->children().indexOf(obj);

    return createIndex(row, 0, obj->parent());
}
