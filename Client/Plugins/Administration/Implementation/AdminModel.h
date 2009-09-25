#ifndef ADMINMODEL_H
#define ADMINMODEL_H

#include <QAbstractItemModel>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"

class Data;
class AdminModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AdminModel(const QHash<quint32, UserData*>&  _users, TreeData *Data);

    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant    headerData ( int section, Qt::Orientation orientation, int role) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

private:
   Data*           rootItem;
   const QHash<quint32,UserData*>& users;
};

#endif // ADMINMODEL_H
