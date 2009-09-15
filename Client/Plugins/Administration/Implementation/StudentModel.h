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
     StudentModel(const QList<UserData*> users);
     ~StudentModel();

     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

 private:
     void setupModelData(const QList<UserData*> users, UserItem *parent);
    UserItem *rootItem;
};

#endif // STUDENTMODEL_H
