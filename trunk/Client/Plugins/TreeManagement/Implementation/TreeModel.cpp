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

    if (role == Qt::DisplayRole || role == Qt::UserRole)
    {

//        qDebug() << ((QObject*)(index.internalPointer()))->property("type");

        if (role == Qt::DisplayRole)
        {

        Tree* node = dynamic_cast<Tree*>(static_cast<QObject*>(index.internalPointer()));
        if (node)
        {
//            qDebug() << "TreeModel::data Tree" << node->Getid();
//            if (index.column() == 1)
                return QVariant(node->GetName());
//            return QVariant(node->Getid());
        }

        }

        //IFile* file = dynamic_cast<IFile*>(static_cast<QObject*>(index.internalPointer()));
        //IFile* file = qobject_cast<IFile*>((QObject*)(index.internalPointer()));
        IFile* file = (IFile*)(index.internalPointer());
        if (file)
        {
//            qDebug() << "TreeModel::data IFile";
//            if (index.column() == 1)
            if (role == Qt::DisplayRole)
                return QVariant(file->getInfo().fileName);
            else
                return QVariant(file->getInfo().id);
//            return QVariant(file->getInfo().id);
        }
    }
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
