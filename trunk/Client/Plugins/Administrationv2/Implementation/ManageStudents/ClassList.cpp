#include "ClassList.h"
#include <QDebug>
#include <QMimeData>
CClassList::CClassList(QWidget *it)
{
    Ls = it;
}

bool CClassList::dropMimeData(QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action)
{
    qDebug() << data->data("id");
	return (false); //TODO return a good value
}
