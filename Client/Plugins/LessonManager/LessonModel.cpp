#include "LessonModel.h"

LessonModel::LessonModel(PluginManager* pluginManager)
{
    this->pluginManager = pluginManager;
    rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0));
}

int LessonModel::columnCount ( const QModelIndex & parent) const
{
    return 1;
}

int LessonModel::rowCount ( const QModelIndex & parent) const
{
    if (!parent.isValid())
        return 1;
    Data* data = (Data*)(parent.internalPointer());
    return data->children().count();
}

QVariant LessonModel::data ( const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
   Data* data = (Data*)(index.internalPointer());
   if (index.column() == 0 && role == Qt::DecorationRole)
        return data->data(0, role);
   return data->data(1, role);
}

QModelIndex LessonModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, rootItem);

    return createIndex(row, column, ((Data*)(parent.internalPointer()))->children().at(row) );
}

QModelIndex LessonModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if (obj == rootItem)
        return QModelIndex();

    if (obj->parent() == rootItem)
        return createIndex(0, 0, rootItem);

    obj = obj->parent();
    return createIndex(obj->parent()->children().indexOf(obj), 0, obj);
}
