#include "ListSelection.h"
#include "Tools.h"
#include <QMapIterator>
#include <QListWidgetItem>
#include <QLabel>
#include <QMimeData>
ListSelection::ListSelection(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _tools = new mytools(treeplugin, userplugin);

      QHBoxLayout *ListLayout = new QHBoxLayout();

       StudentList = new QListWidget();
       ClassList = new QListWidget(this);
/*
StudentList->setSelectionMode(QAbstractItemView::SingleSelection);
ClassList->setSelectionMode(QAbstractItemView::SingleSelection);
StudentList->setDragEnabled (true);
ClassList->setAcceptDrops(true);
*/


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
    //reeWidgetItem *tempitem = new QTreeWidgetItem(QStringList(i.value()));

    tempitem->setData(Qt::UserRole, i.key());
    ClassList->addItem(tempitem);
    //ClassList->insertTopLevelItem(0, tempitem);
    }
}


void ListSelection::updatestudents(QListWidgetItem *item)
{
StudentList->clear();
    foreach (UserData* user, _tools->getStudentfromClass(item->data(Qt::UserRole).toInt()))
    {
        //QMimeData *mimeData = new QMimeData();

            QListWidgetItem *tempitem = new QListWidgetItem(user->name() +" "+ user->surname());
            //tempitem->setData(Qt::UserRole, i.key());

              //  mimeData->setData("id", QVariant(user->id()).toByteArray());

            StudentList->addItem(tempitem);


    }


}

