#include "ClassList.h"
#include <QDebug>
#include <QMimeData>
CClassList::CClassList()
{
    viewport()->setAcceptDrops(true);
    setMovement(QListView::Snap);
    setDragDropMode(QAbstractItemView::DropOnly);


}
