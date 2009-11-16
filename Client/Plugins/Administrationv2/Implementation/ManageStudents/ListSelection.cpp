#include "ListSelection.h"
#include "Tools.h"
#include <QMapIterator>
#include <QListWidgetItem>
#include <QLabel>
#include <QMimeData>

ListSelection::ListSelection(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _tools = new mytools(treeplugin, userplugin);

      QVBoxLayout *ListLayout = new QVBoxLayout();

      ListLayout->setMargin(0);
      ListLayout->setSpacing(0);

       StudentList = new QListWidget();
       ClassList = new QListWidget(this);
       ClassList->setViewMode(QListWidget::IconMode);
       ClassList->setMovement(QListWidget::Static);
       ClassList->setFlow(QListWidget::TopToBottom);
       ClassList->setGridSize(QSize(64, 54));
       ClassList->setWrapping(true);
       ClassList->setMaximumHeight(64);
/*
StudentList->setSelectionMode(QAbstractItemView::SingleSelection);
ClassList->setSelectionMode(QAbstractItemView::SingleSelection);
StudentList->setDragEnabled (true);
ClassList->setAcceptDrops(true);
*/

       QLabel *title = new QLabel(tr("Select a class to view, add or edit students."));
       title->setProperty("isTitle", QVariant(true));
       ListLayout->addWidget(title);
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
    QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Icons/desk.png"), i.value());
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

            QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Icons/students.png"), user->name() +" "+ user->surname());
            tempitem->setData(Qt::UserRole, user->id());
            //tempitem->setData(Qt::UserRole, i.key());

              //  mimeData->setData("id", QVariant(user->id()).toByteArray());

            StudentList->addItem(tempitem);


    }


}

