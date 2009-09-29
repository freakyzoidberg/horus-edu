#include "FilterModel.h"

FilterModel::FilterModel(int _type, QObject *parent)
{
    type = _type;
}

QModelIndex FilterModel::mapFromSource(const QModelIndex & sourceIndex)
{
    return sourceIndex;
}

bool FilterModel::filterAcceptsRow (int source_row, const QModelIndex & source_parent)
{
//        TreeData* node = qobject_cast<TreeData*>((Data*)(source_parent.internalPointer()));
//        if ( ! node)
//                return false;
}
