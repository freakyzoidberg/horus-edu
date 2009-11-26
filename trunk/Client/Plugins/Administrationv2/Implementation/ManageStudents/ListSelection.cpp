/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ListSelection.h"
#include "Tools.h"
#include <QMapIterator>
#include <QListWidgetItem>
#include <QLabel>
#include <QMimeData>
#include <QMessageBox>
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
       ClassList->setSelectionRectVisible(false);
/*
StudentList->setSelectionMode(QAbstractItemView::SingleSelection);
ClassList->setSelectionMode(QAbstractItemView::SingleSelection);
StudentList->setDragEnabled (true);
ClassList->setAcceptDrops(true);
*/

       QLabel *title = new QLabel(tr("Select a class to view, add or edit students."));
       title->setProperty("isTitle", true);
       ListLayout->addWidget(title);
       ListLayout->addWidget(ClassList);
       ListLayout->addWidget(StudentList);

       connect(ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updatestudents(QListWidgetItem *)));
       this->setLayout(ListLayout);
}


void ListSelection::updateall()
{
QMapIterator<int, QString> i(_tools->getallclass());

ClassList->clear();
StudentList->clear();
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
    if ((user->status() == Data::UPTODATE))
    {
        //QMimeData *mimeData = new QMimeData();

            QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Icons/students.png"), user->name() +" "+ user->surname());
            tempitem->setData(Qt::UserRole, user->id());
            //tempitem->setData(Qt::UserRole, i.key());

              //  mimeData->setData("id", QVariant(user->id()).toByteArray());

            StudentList->addItem(tempitem);


    }


}

void ListSelection::updatestudents()
{
    StudentList->clear();


if (ClassList->selectedItems().count() > 0)
    {
    foreach (UserData* user, _tools->getStudentfromClass(ClassList->selectedItems().first()->data(Qt::UserRole).toInt()))
    if ((user->status() == Data::UPTODATE))
    {
        //QMimeData *mimeData = new QMimeData();

            QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Icons/students.png"), user->name() +" "+ user->surname());
            tempitem->setData(Qt::UserRole, user->id());
            //tempitem->setData(Qt::UserRole, i.key());

              //  mimeData->setData("id", QVariant(user->id()).toByteArray());

            StudentList->addItem(tempitem);


    }
    }
}
