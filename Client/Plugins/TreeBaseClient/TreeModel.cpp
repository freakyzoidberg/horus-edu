#include "TreeModel.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"

#include <QDebug>

TreeModel::TreeModel(PluginManager* _pluginManager)
{
    pluginManager = _pluginManager;
    pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0)->dumpObjectTree();
    rootItem = pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0);
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 3;
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;
    //qDebug() << ((QObject*)(parent.internalPointer()))->children().length();
    return ((Data*)(parent.internalPointer()))->children().length();
}
/*
QVariant TreeModel::headerData (int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole)
        return QVariant("");
   return QVariant();
}
*/
QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant("EMPTY");

    Data* obj = ((Data*)(index.internalPointer()));

//   if ( ! obj->inherits("Data"))
//       return QVariant();

   if (role == Qt::DisplayRole)
        return QVariant(((Data*)obj)->data(index.column(), Qt::DisplayRole));
   if (role == Qt::DecorationRole && index.column() == 0)
        return QVariant(((Data*)obj)->data(0, Qt::DecorationRole));

   return QVariant();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, rootItem);

    return createIndex(row, column, ((Data*)(parent.internalPointer()))->children().at(row) );
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();

    Data* obj = (Data*)(((Data*)(index.internalPointer()))->parent());

    if ( ! obj)
        return QModelIndex();

    int row = 0;
    if (obj != rootItem)
        row = obj->children().indexOf(obj);

    return createIndex(row, 0, obj);
}
