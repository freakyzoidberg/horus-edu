#include "StudentModel.h"
#include "UserItem.h"

StudentModel::StudentModel(const QList<UserData*> users)
//     : QAbstractItemModel(parent)
 {
     QList<QVariant> rootData;
     rootData << "Etudiants" << "Id";
     rootItem = new UserItem(rootData);
     setupModelData(users, rootItem);
 }

 StudentModel::~StudentModel()
 {
     delete rootItem;
 }

 int StudentModel::columnCount(const QModelIndex &parent) const
 {
     if (parent.isValid())
         return static_cast<UserItem*>(parent.internalPointer())->columnCount();
     else
         return rootItem->columnCount();
 }

 QVariant StudentModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     UserItem *item = static_cast<UserItem*>(index.internalPointer());

     return item->data(index.column());
 }

 Qt::ItemFlags StudentModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }

 QVariant StudentModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItem->data(section);

     return QVariant();
 }

 QModelIndex StudentModel::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

     UserItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<UserItem*>(parent.internalPointer());

     UserItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }

 QModelIndex StudentModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     UserItem *childItem = static_cast<UserItem*>(index.internalPointer());
     UserItem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
 }

 int StudentModel::rowCount(const QModelIndex &parent) const
 {
     UserItem *parentItem;
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<UserItem*>(parent.internalPointer());

     return parentItem->childCount();
 }

 void StudentModel::setupModelData(const QList<UserData*> users, UserItem *parent)
 {
    QList<UserItem*> parents;
     QList<int> indentations;
     parents << parent;
     indentations << 0;

     int number = 0;

     while (number < users.count())
     {
       /*  int position = 0;
         while (position < lines[number].length()) {
             if (lines[number].mid(position, 1) != " ")
                 break;
             position++;
         }

         QString lineData = lines[number].mid(position).trimmed();
*/
         if (users[number]->level() == 3)
         {
             QList<QVariant> columnData;
             columnData << users[number]->login() << users[number]->id();
/*
             if (position > indentations.last()) {
                 // The last child of the current parent is now the new parent
                 // unless the current parent has no children.

                 if (parents.last()->childCount() > 0) {
                     parents << parents.last()->child(parents.last()->childCount()-1);
                     indentations << position;
                 }
             } else {
                 while (position < indentations.last() && parents.count() > 0) {
                     parents.pop_back();
                     indentations.pop_back();
                 }
             }*/

             // Append a new item to the current parent's list of children.
             parents.last()->appendChild(new UserItem(columnData, parents.last()));
         }

         number++;
     }
 }
