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
        if (obj->objectName() == "ITree")
            return QVariant(((ITree*)obj)->getName());
//        if (obj->objectName() == "IFile")
//            return QVariant(((IFile*)obj)->getInfo().fileName);
    }

//   else if (role == Qt::UserRole &&
//             obj->objectName() == "IFile" &&
//             ((IFile*)obj)->getInfo().mimeType == "x-horus/x-lesson")
//       return QVariant(((IFile*)obj)->getInfo().id);

    else if (role == Qt::DecorationRole)
    {
//        if (obj->objectName() == "IFile")
//        {
//            if (((IFile*)obj)->getInfo().mimeType == "x-horus/x-lesson")
//                return QVariant(QVariant::Icon, &LessonIcon);
//            return QVariant(QVariant::Icon, &FileIcon);
//        }
        if (obj->objectName() == "ITree")
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
    if (obj->objectName() == "ITree")
    {
        int nbChilds = obj->children().length();

//        const QList<IFile*> fileList = fileManager->getNodeFileList(((ITree*)obj)->Getid());

        if (row < nbChilds)
            return createIndex(row, column, obj->children().at(row) );

//        if (nbChilds + fileList.size() > 0)
//            return createIndex(row, column, fileList.at( row - nbChilds ));
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();

    QObject* obj = ((QObject*)(index.internalPointer()));

    ITree* node = 0;
    if (obj->objectName() == "ITree")
    {
        if (obj == obj->parent())
            return QModelIndex();

        node = (ITree*)((ITree*)obj)->parent();
    }
//    else if (obj->objectName() == "IFile")
//        node = Tree::GetNodebyId( ((IFile*)obj)->getInfo().nodeId );

    else
        return QModelIndex();

    if ( ! node->getId())
        return createIndex(0, 0, node);

    return createIndex(((ITree*)node->parent())->findChildren<ITree*>().indexOf(node), 0, node);
}
