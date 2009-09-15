#include "UserItem.h"

#include <QStringList>

 #include "UserItem.h"

 UserItem::UserItem(const QList<QVariant> &data, UserItem *parent)
 {
     parentItem = parent;
     itemData = data;
 }

 UserItem::~UserItem()
 {
     qDeleteAll(childItems);
 }

 void UserItem::appendChild(UserItem *item)
 {
     childItems.append(item);
 }

 UserItem *UserItem::child(int row)
 {
     return childItems.value(row);
 }

 int UserItem::childCount() const
 {
     return childItems.count();
 }

 int UserItem::columnCount() const
 {
     return itemData.count();
 }

 QVariant UserItem::data(int column) const
 {
     return itemData.value(column);
 }

 UserItem *UserItem::parent()
 {
     return parentItem;
 }

 int UserItem::row() const
 {
     if (parentItem)
         return parentItem->childItems.indexOf(const_cast<UserItem*>(this));

     return 0;
 }
