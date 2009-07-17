#include "TreeModel.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"

#include <QDebug>

QIcon TreeModel::LessonIcon(":/Icons/LessonIcon.png");
QIcon TreeModel::SubjectIcon(":/Icons/MatiereIcon.png");
QIcon TreeModel::GradeIcon(":/Icons/ClassIcon.png");
QIcon TreeModel::FileIcon(":/Icons/FileIcon.png");
QIcon TreeModel::GroupIcon(":/Icons/GroupIcon.png");
QIcon TreeModel::RootIcon(":/Icons/RootIcon.png");
QIcon TreeModel::DefaultIcon(":/Icons/DefaultIcon.png");

TreeModel::TreeModel(PluginManager* _pluginManager)
{
    pluginManager = _pluginManager;
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 5;
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;
    qDebug() << ((QObject*)(parent.internalPointer()))->children().length();
    return ((QObject*)(parent.internalPointer()))->children().length();
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
        return QVariant();

    QObject* obj = ((QObject*)(index.internalPointer()));

   if ( ! obj->inherits("Data"))
       return QVariant();

//   if (role == Qt::DisplayRole)
//        return QVariant(((Data*)obj)->data(index.column() + 1, Qt::DisplayRole));
//    else
        return QVariant(((Data*)obj)->data(index.column()    , role));
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0));

    return createIndex(row, column, ((QObject*)(parent.internalPointer()))->children().at(row) );
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
//    if ( ! index.isValid())
//        return QModelIndex();

    QObject* obj = ((QObject*)(index.internalPointer()))->parent();

    if ( ! obj)
        return QModelIndex();

    if ( ! obj->parent())
        return createIndex(0, 0, obj);

    return createIndex(obj->children().indexOf(obj), 0, obj);
}
