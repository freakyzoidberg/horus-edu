#include "StudentModel.h"

StudentModel::StudentModel(const QHash<quint32, UserData*>&  _users, int role)
//     : QAbstractItemModel(parent)
 {

    foreach (UserData* user, _users)
    {
        if (role == 1)
            if (user->level() == 3)
                users.append(user);
        if (role == 2)
            if (user->level() == 2)
                users.append(user);
    }
//     QList<QVariant> rootData;
//     rootData << "Id" << "Etudiants";
//     rootItem = new UserItem(rootData);
//     setupModelData(users, rootItem);
 }

 StudentModel::~StudentModel()
 {
//     delete rootItem;
 }

 int StudentModel::columnCount(const QModelIndex &parent) const
 {
//     if (parent.isValid())
         return 1;//users.size();
//     else
//         return rootItem->columnCount();
 }

 QVariant StudentModel::data(const QModelIndex &index, int role) const
 {
     UserData *item = static_cast<UserData*>(index.internalPointer());

     if (role == Qt::DisplayRole)
         return item->data(index.column() + 1, role);
     else
         return item->data(index.column(), role);
 }

 QVariant StudentModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return "Students";

     return QVariant();
 }

 QModelIndex StudentModel::index(int row, int column, const QModelIndex &parent)
             const
 {
//     if (!hasIndex(row, column, parent))
//         return QModelIndex();

//     UserData *item = qobject_cast<UserData*>(index.internalPointer());
//     UserItem *parentItem;

//     if (!parent.isValid())
//         parentItem = rootItem;
//     else
//         parentItem = static_cast<UserItem*>(parent.internalPointer());

//     UserItem *childItem = parentItem->child(row);
//     if (childItem)
         return createIndex(row, column, users.at(row));
//     else
//         return QModelIndex();
 }

 QModelIndex StudentModel::parent(const QModelIndex &index) const
 {
//     if (!index.isValid())
         return QModelIndex();
//
//     UserItem *childItem = static_cast<UserItem*>(index.internalPointer());
//     UserItem *parentItem = childItem->parent();
//
//     if (parentItem == rootItem)
//         return QModelIndex();
//
//     return createIndex(parentItem->row(), 0, parentItem);
 }

 int StudentModel::rowCount(const QModelIndex &parent) const
 {
     if ( ! parent.isValid())

         return users.size();
     else
         return 0;
//     UserItem *parentItem;
//     if (parent.column() > 0)
//         return 0;
//
//     if (!parent.isValid())
//         parentItem = rootItem;
//     else
//         parentItem = static_cast<UserItem*>(parent.internalPointer());
//
//     return parentItem->childCount();
 }

// void StudentModel::setupModelData(const QList<UserData*> users, UserItem *parent)
// {
//    QList<UserItem*> parents;
//     QList<int> indentations;
//     parents << parent;
//     indentations << 0;
//
//     int number = 0;
//
//     while (number < users.count())
//     {
//         if (users[number]->level() == 3)
//         {
//             QList<QVariant> columnData;
//             columnData << users[number]->id() << users[number]->login();
//             parents.last()->appendChild(new UserItem(columnData, parents.last()));
//         }
//
//         number++;
//     }
// }
