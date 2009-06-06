#include "TreeModel.h"
#include "Tree.h"
#include "../../IFile.h"

#include <QDebug>

TreeModel::TreeModel(IFileManager* fileManager)
{
//    fileManager= _fileManager;
    //QList<IFile*> list = fileManager->getFullFileList();
    filesById = fileManager->getFullFileList();
    for (QHash<quint32,IFile*>::const_iterator i = filesById.begin(); i != filesById.end(); ++i)
        filesByParent.insertMulti((*i)->getInfo().nodeId, (*i));
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 1;
}

QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

    QObject* obj = ((QObject*)index.internalPointer());
    qDebug() << obj->objectName();

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

    return QVariant();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, Tree::GetNodebyId(0));

    Tree* node = dynamic_cast<Tree*>(static_cast<QObject*>(parent.internalPointer()));
    if (node)
    {
        int nbChilds = node->GetSonsNode().size();
        int nbFiles = filesByParent.values(node->Getid()).size();

//        qDebug() << "TreeModel::index" << nbChilds << nbFiles;

        if (nbChilds + nbFiles <= 0)
            return QModelIndex();

        if (row < nbChilds)
            return createIndex(row, column, node->GetSonsNode().at(row));

//        qDebug() << "put file pointer" << filesByParent.values(node->Getid()).at( row - nbChilds )->getInfo();
        return createIndex(row, column, filesByParent.values(node->Getid()).at( row - nbChilds ));
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();

    Tree* node = dynamic_cast<Tree*>(static_cast<QObject*>(index.internalPointer()));
    if (node)
    {
//         qDebug() << "TreeModel::parent Tree" << node->Getid();
        if (node == node->GetParent())
            return QModelIndex();

        node = node->GetParent();
    }
    else
    {
//        qDebug() << "TreeModel::parent IFile";
//        IFile* file = dynamic_cast<IFile*>(static_cast<QObject*>(index.internalPointer()));
        IFile* file = (IFile*)(index.internalPointer());
        if (file)
        {
//            qDebug() << file->getInfo();
            node = Tree::GetNodebyId( file->getInfo().nodeId );
        }
        else
            return QModelIndex();
    }

    if ( ! node->Getid())
        return createIndex(0, 0, node);

    return createIndex(node->GetParent()->GetSonsNode().indexOf(node), 0, node);
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;

    Tree* p = dynamic_cast<Tree*>(static_cast<QObject*>(parent.internalPointer()));
    if ( ! p)
        return 0;

//    qDebug() << "TreeModel::rowCount" << p->Getid() << p->GetSonsNode().size() + filesByParent.values(p->Getid()).size();
    return p->GetSonsNode().size() + filesByParent.values(p->Getid()).size();
}

QIcon TreeModel::MatiereIcon(":/Icons/MatiereIcon.png");

QIcon TreeModel::ClassIcon(":/Icons/ClassIcon.png");

QIcon TreeModel::FileIcon(":/Icons/FileIcon.png");
