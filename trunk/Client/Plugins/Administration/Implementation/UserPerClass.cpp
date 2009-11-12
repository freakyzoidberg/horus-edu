#include "UserPerClass.h"

UserPerClass::UserPerClass(const QHash<quint32, UserData*>&  _users, int _id, QObject *parent)
        :  QAbstractListModel(parent), users(_users)
{
    id = _id;
}

QVariant UserPerClass::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();
    //qDebug() << role << " : " << index.row();
    if (index.row() >= users.size())
         return QVariant();
    int i = 0;
    foreach (UserData* user, users)
    {
        if(user->level() == 3)
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
    }
    return QVariant();
}

int UserPerClass::rowCount(const QModelIndex &parent) const
{
    quint32 i = 0;
    foreach (UserData* user, users)
        if(user->level() == 3)
        {
            if (id != -10)
            {
                if (user->node()->id() == id)
                    i++;
            }
            else
                i++;
        }
    return i;
    //return users.size();
}
