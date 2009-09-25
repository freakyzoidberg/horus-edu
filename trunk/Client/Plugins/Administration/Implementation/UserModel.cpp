#include "UserModel.h"

UserModel::UserModel(const QHash<quint32, UserData*>&  _users, int _level)
        : users(_users)
{
    level = _level;
}

int UserModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    UserData *item = static_cast<UserData*>(index.internalPointer());
    if (item == NULL)
       index.data(role);
    if (role == Qt::DisplayRole)
        return item->data(index.column() + 1, role);
    else
        return item->data(index.column(), role);
}

QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return tr("Students");

    return QVariant();
}

QModelIndex UserModel::index(int row, int column, const QModelIndex &parent) const
{
    int i = 0;
    foreach (UserData* user, users)
        if (user->level() == level)
        {
            if (i == row)
                return createIndex(row, column, user);
            i++;
        }
    return QModelIndex();
}

QModelIndex UserModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int UserModel::rowCount(const QModelIndex &parent) const
{
//	TreeData* node = qobject_cast<TreeData*>((Data*)(parent.internalPointer()));
//	if ( ! node)
//		return 0;
//
//
//    quint32 i = 0;
//    foreach (UserData* user, users)
//        if (user->level() == level)
//            i++;
//    return i;
}
