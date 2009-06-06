#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMultiHash>
#include <QtGui/QIcon>
#include <QAbstractItemModel>
#include "../../IFilePlugin.h"

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(IFileManager* fileManager);

    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
//    QVariant    headerData ( int section, Qt::Orientation orientation, int role) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

private:
    IFileManager* fileManager;

    static QIcon    ClassIcon;
    static QIcon    MatiereIcon;
    static QIcon    FileIcon;
};

#endif // TREEMODEL_H
