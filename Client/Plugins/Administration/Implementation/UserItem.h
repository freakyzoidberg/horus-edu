#ifndef USERITEM_H
#define USERITEM_H

 #include <QList>
 #include <QVariant>

class UserItem
{
 public:
     UserItem(const QList<QVariant> &data, UserItem *parent = 0);
     ~UserItem();

     void appendChild(UserItem *child);

     UserItem *child(int row);
     int childCount() const;
     int columnCount() const;
     QVariant data(int column) const;
     int row() const;
     UserItem *parent();

 private:
     QList<UserItem*> childItems;
     QList<QVariant> itemData;
     UserItem *parentItem;
};

#endif // USERITEM_H
