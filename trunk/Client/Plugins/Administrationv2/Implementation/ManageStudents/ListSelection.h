#ifndef LISTSELECTION_H
#define LISTSELECTION_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTreeWidget>
#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"
#include "Tools.h"
#include "ClassList.h"
class CClassList;
class ListSelection : public QWidget
{
    Q_OBJECT
public:
    ListSelection(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin);
    QListWidget *StudentList;
    QListWidget *ClassList;
     void updateall();

private:
     mytools *_tools;

 private slots:
    void updatestudents(QListWidgetItem* item);
};
#endif // LISTSELECTION_H
