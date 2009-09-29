#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    public:
        FilterModel(int _type, QObject *parent = 0);
    private:
        QModelIndex mapFromSource (const QModelIndex & sourceIndex);
        bool        filterAcceptsRow(int source_row, const QModelIndex & source_parent);
        int         type;
};

#endif // FILTERMODEL_H
