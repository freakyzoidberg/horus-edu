#include "TreeModel.h"
#include "Tree.h"
#include "../../IFile.h"

#include <QDebug>

TreeModel::TreeModel(IFileManager* fileManager)
{
//    fileManager= _fileManager;
    //QList<IFile*> list = fileManager->getFullFileList();
//    filesById = fileManager->getFullFileList();
  //  for (QHash<quint32,IFile*>::const_iterator i = filesById.begin(); i != filesById.end(); ++i)
 //       filesByParent.insertMulti((*i)->getInfo().id, (*i));
}

int TreeModel::columnCount ( const QModelIndex & ) const
{
    return 2;
}

QVariant TreeModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        Tree* node = dynamic_cast<Tree*>((QObject*)(index.internalPointer()));
        if (node)
        {
            qDebug() << "TreeModel::data Tree" << node->Getid();
            if (index.column() == 1)
                return QVariant(node->GetName());
            return QVariant(node->Getid());
        }

        IFile* file = dynamic_cast<IFile*>((QObject*)(index.internalPointer()));
        if (file)
        {
            qDebug() << "TreeModel::data IFile";
            if (index.column() == 1)
                return QVariant(file->getInfo().fileName);
            return QVariant(file->getInfo().id);
        }
    }
    return QVariant();
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, Tree::GetNodebyId(0));

    Tree* node = dynamic_cast<Tree*>((QObject*)(parent.internalPointer()));
    if (node)
    {
        if (node->GetSonsNode().size() <= 0)
            return QModelIndex();

        if (node->GetSonsNode().size() > row)
            return createIndex(row, column, node->GetSonsNode().at(row));

         qDebug() << "TreeModel::index";
        return createIndex(row, column, filesByParent.values(node->Getid()).at( row - node->GetSonsNode().size() ));
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
    if ( ! index.isValid())
        return QModelIndex();

    Tree* node = dynamic_cast<Tree*>((QObject*)(index.internalPointer()));
    if (node)
    {
         qDebug() << "TreeModel::parent Tree" << node->Getid();
        if (node == node->GetParent())
            return QModelIndex();

        node = node->GetParent();
    }
    else
    {
        qDebug() << "TreeModel::parent IFile";
        IFile* file = dynamic_cast<IFile*>((QObject*)(index.internalPointer()));
        if (file)
            node = Tree::GetNodebyId( file->getInfo().nodeId );
    }

    if (node == node->GetParent())
        return createIndex(0, 0, node);

    return createIndex(node->GetParent()->GetSonsNode().indexOf(node), 0, node);
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return 1;

    Tree* p = dynamic_cast<Tree*>((QObject*)(parent.internalPointer()));
    if ( ! p)
        return 0;

    qDebug() << "TreeModel::rowCount" << p->GetSonsNode().size() + filesByParent.values(p->Getid()).size();
    return p->GetSonsNode().size() + filesByParent.values(p->Getid()).size();
}
