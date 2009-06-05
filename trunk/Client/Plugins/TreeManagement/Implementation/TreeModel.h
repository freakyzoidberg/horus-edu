#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMultiHash>

#include <QAbstractItemModel>
#include "../../IFilePlugin.h"

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(IFileManager* fileManager);
    /*** virtual in QAbstractItemModel ***/
    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    /**************************************/

private:
//    IFileManager* fileManager;
    QMultiHash<quint32,IFile*> filesByParent;
    QHash<quint32,IFile*>      filesById;
};

#endif // TREEMODEL_H
