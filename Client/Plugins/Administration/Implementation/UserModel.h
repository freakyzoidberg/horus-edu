#ifndef USERMODEL_H
#define USERMODEL_H


#include <QAbstractItemModel>
 #include <QModelIndex>
 #include <QVariant>
#include "../../../../Common/UserData.h"


class UserModel: public QAbstractListModel
{
    Q_OBJECT

    public:
     UserModel(const QHash<quint32, UserData*>& users, QObject *parent = 0);

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
     quint32                         level;
};

#endif // UserModel_H
