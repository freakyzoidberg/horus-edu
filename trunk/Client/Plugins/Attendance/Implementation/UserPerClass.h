#ifndef USERPERCLASS_H
#define USERPERCLASS_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "../../../../Common/UserData.h"
#include "../../../../Common/TreeData.h"

class UserPerClass : public QAbstractListModel
{
    Q_OBJECT

    public:
     UserPerClass(const QHash<quint32, UserData*>& users, int _id, QObject *parent = 0);

     QVariant data(const QModelIndex &index, int role) const;
//     QVariant headerData(int section, Qt::Orientation orientation,
//                         int role = Qt::DisplayRole) const;
//     QModelIndex index(int row, int column,
//                       const QModelIndex &parent = QModelIndex()) const;
//     QModelIndex parent(const QModelIndex &index) const;
//     int columnCount(const QModelIndex &parent = QModelIndex()) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;


private:
     const QHash<quint32,UserData*>& users;
     quint32                         id;
};


#endif // USERPERCLASS_H
