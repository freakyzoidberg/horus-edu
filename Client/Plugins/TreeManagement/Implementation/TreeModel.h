#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
public:
    /*** virtual in QAbstractItemModel ***/
    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    /**************************************/
};

#endif // TREEMODEL_H
