#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H


#include <QAbstractItemModel>
 #include <QModelIndex>
 #include <QVariant>
#include "../../../../Common/UserData.h"

class UserItem;

class StudentModel: public QAbstractItemModel
{
    Q_OBJECT

    public:
     StudentModel(const QHash<quint32, UserData*>& users, int level);

     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
     const QHash<quint32,UserData*>& users;
     quint32                         level;
};

#endif // STUDENTMODEL_H
