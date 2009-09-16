#include "TeacherModel.h"

 #include "UserItem.h"

TeacherModel::TeacherModel(const QList<UserData*> users)
//     : QAbstractItemModel(parent)
 {
     QList<QVariant> rootData;
     rootData << "Id" << "Etudiants";
     rootItem = new UserItem(rootData);
     setupModelData(users, rootItem);
 }

 TeacherModel::~TeacherModel()
 {
     delete rootItem;
 }

 int TeacherModel::columnCount(const QModelIndex &parent) const
 {
     if (parent.isValid())
         return static_cast<UserItem*>(parent.internalPointer())->columnCount();
     else
         return rootItem->columnCount();
 }

 QVariant TeacherModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     UserItem *item = static_cast<UserItem*>(index.internalPointer());

     return item->data(index.column());
 }

 Qt::ItemFlags TeacherModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }

 QVariant TeacherModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItem->data(section);

     return QVariant();
 }

 QModelIndex TeacherModel::index(int row, int column, const QModelIndex &parent)
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

 QModelIndex TeacherModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     UserItem *childItem = static_cast<UserItem*>(index.internalPointer());
     UserItem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
 }

 int TeacherModel::rowCount(const QModelIndex &parent) const
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

 void TeacherModel::setupModelData(const QList<UserData*> users, UserItem *parent)
 {
    QList<UserItem*> parents;
     QList<int> indentations;
     parents << parent;
     indentations << 0;

     int number = 0;

     while (number < users.count())
     {
         if (users[number]->level() == 2)
         {
             QList<QVariant> columnData;
             columnData << users[number]->id() << users[number]->login();
             parents.last()->appendChild(new UserItem(columnData, parents.last()));
         }

         number++;
     }
 }
