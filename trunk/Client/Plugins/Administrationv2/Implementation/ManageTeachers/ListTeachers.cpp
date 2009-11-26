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
#include				"ListTeachers.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

ListTeachers::ListTeachers(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*leftLayout;
	QBoxLayout			*rightLayout;
	QFrame				*informationsFrame;
	QLabel				*informationsTitle;
	QLabel				*actionsTitle;
	QLabel				*listTitle;
	QPushButton			*addButton;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	listTitle = new QLabel(tr("Select a teacher to view or edit it."));
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	filter = new QSortFilterProxyModel(this);
	filter->setSourceModel(pluginManager->findPlugin<UserDataPlugin*>()->listModel());
	filter->setFilterRole(Data::FILTER_ROLE);
	filter->setFilterKeyColumn(0);
	filter->setFilterFixedString("TEACHER");
	listView = new QListView(this);
	listView->setSelectionMode(QAbstractItemView::SingleSelection);
	listView->setDragEnabled(true);
	listView->setAcceptDrops(true);
	listView->setDropIndicatorShown(true);	listView->setModel(filter);
	listView->setModel(filter);
	leftLayout->addWidget(listView);
	mainLayout->addLayout(leftLayout);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(2);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
    informationsLayout->setSpacing(0);
    informationsLayout->setMargin(0);
	informationsFrame->setMinimumWidth(200);
	informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
    informationsTitle->setProperty("isTitle", true);
    informationsTitle->setProperty("isRound", true);
	informationsLayout->addWidget(informationsTitle);
	displayer = new DisplayTeacher(informationsFrame);
	informationsLayout->addWidget(displayer);
	rightLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	rightLayout->addWidget(actionsTitle);
	addButton = new QPushButton(QIcon(":/Icons/add-teachers.png"), tr("Add a teacher"), this);
	rightLayout->addWidget(addButton);
	editButton = new QPushButton(QIcon(":/Icons/edit-teachers.png"), tr("Edit this teacher"), this);
	editButton->setDisabled(true);
	rightLayout->addWidget(editButton);
	deleteButton = new QPushButton(QIcon(":/Icons/remove-teachers.png"), tr("Delete this teacher"), this);
	deleteButton->setDisabled(true);
	rightLayout->addWidget(deleteButton);
	rightLayout->addWidget(new QWidget(this), 1);
	mainLayout->addLayout(rightLayout);
	connect(listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(TeacherSelected(const QModelIndex &, const QModelIndex &)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(TeacherAdded()));
	connect(editButton, SIGNAL(clicked()), this, SLOT(TeacherEdited()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(TeacherDeleted()));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataCreated(Data *)), this, SLOT(TeacherUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataUpdated(Data *)), this, SLOT(TeacherUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataRemoved(Data *)), this, SLOT(TeacherUpdated(Data *)));
}

void					ListTeachers::TeacherSelected(const QModelIndex &current, const QModelIndex &)
{
	if (current.isValid() && current == listView->currentIndex())
	{
		qDebug() << "Teacher" << current.internalPointer() << current.row();
		editButton->setDisabled(false);
		deleteButton->setDisabled(false);
		delete displayer;
		displayer = new DisplayTeacher(this, (UserData*)(filter->mapToSource(current).internalPointer()));
		informationsLayout->addWidget(displayer);
	}
}

void					ListTeachers::TeacherAdded()
{
	emit editTeacher(0);
}

void					ListTeachers::TeacherEdited()
{
	emit editTeacher((UserData*)(filter->mapToSource(listView->selectionModel()->currentIndex()).internalPointer()));
}

void					ListTeachers::TeacherDeleted()
{
	QMessageBox			*confirm;
	int					ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + listView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		((UserData*)(filter->mapToSource(listView->selectionModel()->currentIndex()).internalPointer()))->remove();
}

void					ListTeachers::TeacherUpdated(Data *)
{
	listView->update();
}
