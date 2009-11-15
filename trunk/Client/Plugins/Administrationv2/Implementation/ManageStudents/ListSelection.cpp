#include "ListSelection.h"
#include "Tools.h"
#include <QMapIterator>
#include <QListWidgetItem>
ListSelection::ListSelection(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _tools = new mytools(treeplugin, userplugin);

       QHBoxLayout *ListLayout = new QHBoxLayout();

       StudentList = new QListWidget();
       ClassList = new QListWidget();
       ListLayout->addWidget(ClassList);
       ListLayout->addWidget(StudentList);

       connect(ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updatestudents(QListWidgetItem *)));
       this->setLayout(ListLayout);
}


void ListSelection::updateall()
{
QMapIterator<int, QString> i(_tools->getallclass());

while (i.hasNext())
    {
    i.next();
    QListWidgetItem *tempitem = new QListWidgetItem(i.value());
    tempitem->setData(Qt::UserRole, i.key());
    ClassList->addItem(tempitem);
    }
}


void ListSelection::updatestudents(QListWidgetItem *item)
{
StudentList->clear();
    foreach (UserData* user, _tools->getStudentfromClass(item->data(Qt::UserRole).toInt()))
    {

            QListWidgetItem *tempitem = new QListWidgetItem(user->name() +" "+ user->surname());
            //tempitem->setData(Qt::UserRole, i.key());
            StudentList->addItem(tempitem);

    }


}

