#include "TreeModel.h"
#include "Tree.h"
#include "../../IFile.h"

#include <QDebug>

QIcon TreeModel::MatiereIcon(":/Icons/MatiereIcon.png");
QIcon TreeModel::ClassIcon(":/Icons/ClassIcon.png");
QIcon TreeModel::FileIcon(":/Icons/FileIcon.png");

TreeModel::TreeModel(IFileManager* _fileManager)
{
    fileManager = _fileManager;
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

    return ((ITree*)obj)->GetSonsNode().size() + fileManager->countNodeFileList( ((ITree*)obj)->Getid() );
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
            return QVariant(((ITree*)obj)->GetName());
        if (obj->objectName() == "IFile")
            return QVariant(((IFile*)obj)->getInfo().fileName);
    }

   else if (role == Qt::UserRole &&
             obj->objectName() == "IFile")
        return QVariant(((IFile*)obj)->getInfo().id);

    else if (role == Qt::DecorationRole)
    {
        if (obj->objectName() == "IFile")
            return QVariant(QVariant::Icon, &FileIcon);
        if (obj->objectName() == "ITree")
            return QVariant(QVariant::Icon, &MatiereIcon);
    }

    return QVariant();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, Tree::GetNodebyId(0));

    QObject* obj = ((QObject*)(parent.internalPointer()));
    if (obj->objectName() == "ITree")
    {
        int nbChilds = ((ITree*)obj)->GetSonsNode().size();

        const QList<IFile*> fileList = fileManager->getNodeFileList(((ITree*)obj)->Getid());

        if (row < nbChilds)
            return createIndex(row, column, ((ITree*)obj)->GetSonsNode().at(row) );

        if (nbChilds + fileList.size() > 0)
            return createIndex(row, column, fileList.at( row - nbChilds ));
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
        if (((ITree*)obj) == ((ITree*)obj)->GetParent())
            return QModelIndex();

        node = ((ITree*)obj)->GetParent();
    }
    else if (obj->objectName() == "IFile")
        node = Tree::GetNodebyId( ((IFile*)obj)->getInfo().nodeId );

    else
        return QModelIndex();

    if ( ! node->Getid())
        return createIndex(0, 0, node);

    return createIndex(node->GetParent()->GetSonsNode().indexOf(node), 0, node);
}
