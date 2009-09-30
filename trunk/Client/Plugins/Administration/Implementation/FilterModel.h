#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"

class FilterModel : public QAbstractProxyModel
{
    Q_OBJECT
    public:
        FilterModel(int _type, QObject *parent = 0);
    private:
        QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
        QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
        QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
        QModelIndex parent(const QModelIndex &index) const;
        int         rowCount(const QModelIndex &index=QModelIndex()) const;
        int         columnCount(const QModelIndex &index=QModelIndex()) const;
        int         type;
};

#endif // FILTERMODEL_H
