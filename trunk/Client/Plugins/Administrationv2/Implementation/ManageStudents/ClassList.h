#ifndef CCLASSLIST_H
#define CCLASSLIST_H

#include <QTreeWidget>
#include "ListSelection.h"
class CClassList : public QTreeWidget
{
public:
    CClassList(QWidget *it);

    bool dropMimeData ( QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action );
private:
QWidget *Ls;

};

#endif // CLASSLIST_H
