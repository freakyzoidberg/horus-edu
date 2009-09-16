#include "StudentModel.h"

StudentModel::StudentModel(const QHash<quint32, UserData*>&  _users, int _level)
        : users(_users)
{
    level = _level;
}
int StudentModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
    UserData *item = static_cast<UserData*>(index.internalPointer());

    if (role == Qt::DisplayRole)
        return item->data(index.column() + 1, role);
    else
        return item->data(index.column(), role);
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return "Students";

    return QVariant();
}

QModelIndex StudentModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex StudentModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int StudentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    quint32 i = 0;
    foreach (UserData* user, users)
        if (user->level() == level)
            i++;

    return i;
}
