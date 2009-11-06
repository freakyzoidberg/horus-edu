#include "MailAbstractModel.h"

int MailAbstractModel::rowCount(const QModelIndex &parent) const
    {
        return stringList.count();
    }



QVariant MailAbstractModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        if (index.row() < 0 || index.row() >= stringList.size())
            return QVariant();

        if (role == Qt::DisplayRole)
            return stringList.at(index.row());
        else
            return QVariant();
    }

QVariant MailAbstractModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
            return QString("Column %1").arg(section);
        else
            return QString("Row %1").arg(section);
    }
