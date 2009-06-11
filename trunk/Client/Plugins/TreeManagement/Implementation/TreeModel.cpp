#include "TreeModel.h"
#include "Tree.h"

#include <QDebug>

QIcon TreeModel::LessonIcon(":/Icons/LessonIcon.png");
QIcon TreeModel::SubjectIcon(":/Icons/MatiereIcon.png");
QIcon TreeModel::GradeIcon(":/Icons/ClassIcon.png");
QIcon TreeModel::FileIcon(":/Icons/FileIcon.png");
QIcon TreeModel::GroupIcon(":/Icons/GroupIcon.png");
QIcon TreeModel::RootIcon(":/Icons/RootIcon.png");
QIcon TreeModel::DefaultIcon(":/Icons/DefaultIcon.png");

TreeModel::TreeModel()
{
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 1;
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;

    QObject* obj = ((QObject*)(parent.internalPointer()));
    if (obj->objectName() != "ITree")
        return 0;

//    return ((ITree*)obj)->GetSonsNode().size() + fileManager->countNodeFileList( ((ITree*)obj)->Getid() );
    return ((ITree*)obj)->children().length();
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

   if (role == Qt::DisplayRole)
    {
        if (obj->inherits("ITree"))
            return QVariant(((ITree*)obj)->getName());
//        if (obj->inherits("IFile"))
//            return QVariant(((IFile*)obj)->getInfo().fileName);
    }

//   else if (role == Qt::UserRole &&
//             obj->inherits("IFile") &&
//             ((IFile*)obj)->getInfo().mimeType == "x-horus/x-lesson")
//       return QVariant(((IFile*)obj)->getInfo().id);

    else if (role == Qt::DecorationRole)
    {
//        if (obj->inherits("IFile"))
//        {
//            if (((IFile*)obj)->getInfo().mimeType == "x-horus/x-lesson")
//                return QVariant(QVariant::Icon, &LessonIcon);
//            return QVariant(QVariant::Icon, &FileIcon);
//        }
        if (obj->inherits("ITree"))
        {
            if (((ITree*)obj)->getType() == "ROOT")
                return QVariant(QVariant::Icon, &RootIcon);
            if (((ITree*)obj)->getType() == "GROUP")
                return QVariant(QVariant::Icon, &GroupIcon);
            if (((ITree*)obj)->getType() == "GRADE")
                return QVariant(QVariant::Icon, &GradeIcon);
            if (((ITree*)obj)->getType() == "SUBJECT")
                return QVariant(QVariant::Icon, &SubjectIcon);
            return QVariant(QVariant::Icon, &DefaultIcon);
        }
    }

    return QVariant();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, Tree::getNodeById(0));

    QObject* obj = ((QObject*)(parent.internalPointer()));
    return createIndex(row, column, obj->children().at(row) );
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

    return createIndex(obj->parent()->children().indexOf(obj), 0, obj);
}
