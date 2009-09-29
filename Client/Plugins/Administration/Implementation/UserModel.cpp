#include "UserModel.h"

UserModel::UserModel(const QHash<quint32, UserData*>&  _users, QObject *parent)
        :  QAbstractListModel(parent), users(_users)
{
    //level = _level;
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();
    //qDebug() << role << " : " << index.row();
    if (index.row() >= users.size())
         return QVariant();
    int i = 0;
    foreach (UserData* user, users)
    {
        if (index.row() == i)
        {
            if (role == Qt::DisplayRole)
                return user->login();
            else if (role == Qt::EditRole)
                return user->login();
            else if (role == Qt::UserRole)
                return user->id();
        }
        i++;
    }
    return QVariant();
}

int UserModel::rowCount(const QModelIndex &parent) const
{
    quint32 i = 0;
    foreach (UserData* user, users)
            i++;
    return i;
    //return users.size();
}
//
//QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return tr("Users");
//
//    return QVariant();
//}
//
//QModelIndex UserModel::index(int row, int column, const QModelIndex &parent) const
//{
//    int i = 0;
//    foreach (UserData* user, users)
//        if (user->level() == level)
//        {
//            if (i == row)
//                return createIndex(row, column, user);
//            i++;
//        }
//    return QModelIndex();
//}
//
//QModelIndex UserModel::parent(const QModelIndex &index) const
//{
//    return QModelIndex();
//}
//
//
//int UserModel::columnCount(const QModelIndex &parent) const
//{
//    return 1;
//}
//    if (role == Qt::DisplayRole)
//        return item->data(index.column() + 1, role);
//    else
//        return item->data(index.column(), role);
