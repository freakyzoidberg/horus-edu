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
#include				"ListUser.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>
#include				<QHeaderView>

ListUser::ListUser(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin, int userLevel) : QWidget(parent)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*leftLayout;
	QBoxLayout			*rightLayout;
	QFrame				*informationsFrame;
	QLabel				*informationsTitle;
	QLabel				*actionsTitle;
	QLabel				*listTitle;
	QString				userFilterString;
	bool				needFilter;

        listTitle = new QLabel(tr("Select an user to add or show his attendance."));
        userFilterString = "STUDENT";
        addButton = new QPushButton(QIcon(":/Icons/add-desk.png"), tr("Add attendance"), this);
        editButton = new QPushButton(QIcon(":/Icons/edit-desk.png"), tr("Show attendances"), this);
        deleteButton = new QPushButton(QIcon(":/Icons/remove-desk.png"), tr("Clean attendances"), this);
        needFilter = true;
	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        mainLayout->setSpacing(0);
        mainLayout->setMargin(2);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	if (needFilter)
	{
		gradeFilter = new QSortFilterProxyModel(this);
		gradeFilter->setSourceModel(treeDataPlugin->listModel());
		gradeFilter->setFilterRole(Qt::DisplayRole);
		gradeFilter->setFilterKeyColumn(1);
		gradeFilter->setDynamicSortFilter(true);
		gradeFilter->setFilterFixedString("GRADE");
		classListView = new QListView(this);
		classListView->setSelectionMode(QAbstractItemView::SingleSelection);
		classListView->setViewMode(QListView::IconMode);
		classListView->setMovement(QListView::Static);
		classListView->setFlow(QListView::TopToBottom);
		classListView->setGridSize(QSize(64, 54));
		classListView->setWrapping(true);
		classListView->setMaximumHeight(64);
		classListView->setSelectionRectVisible(false);
		classListView->setDragEnabled(false);
		classListView->setAcceptDrops(true);
		classListView->viewport()->setAcceptDrops(true);
		classListView->setDropIndicatorShown(true);
		classListView->setModel(gradeFilter);
		leftLayout->addWidget(classListView);
	}
	else
		classListView = 0;
	userFilter = new QSortFilterProxyModel(this);
	userFilter->setSourceModel(userDataPlugin->listModel());
	userFilter->setFilterRole(Data::FILTER_ROLE);
	userFilter->setFilterKeyColumn(0);
	userFilter->setFilterFixedString(userFilterString);
	userFilter->setDynamicSortFilter(true);
	classFilter = new QSortFilterProxyModel(this);
	classFilter->setSourceModel(userFilter);
	classFilter->setFilterRole(Qt::UserRole);
	classFilter->setFilterKeyColumn(0);
	classFilter->setDynamicSortFilter(true);
	userListView = new QTableView(this);
	userListView->setShowGrid(false);
	userListView->verticalHeader()->hide();
	userListView->setSortingEnabled(true);
	userListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	userListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	userListView->setDragEnabled(true);
	userListView->setAcceptDrops(false);
	userListView->setModel(classFilter);
	userListView->setColumnHidden(0, true);
	userListView->setColumnHidden(1, true);
	userListView->setColumnHidden(4, true);
	userListView->setColumnHidden(5, true);
	userListView->setColumnHidden(6, true);
	userListView->setColumnHidden(7, true);
	userListView->setColumnHidden(8, true);
	userListView->setColumnHidden(9, true);
	userListView->setColumnHidden(10, true);
	leftLayout->addWidget(userListView);
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
	informations = new InformationsUser(informationsFrame);
	informationsLayout->addWidget(informations);
	rightLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
        actionsTitle->setProperty("isTitle", true);
        actionsTitle->setProperty("isRound", true);
	rightLayout->addWidget(actionsTitle);
        addButton->setDisabled(true);
	rightLayout->addWidget(addButton);
	editButton->setDisabled(true);
	rightLayout->addWidget(editButton);
	deleteButton->setDisabled(true);
	rightLayout->addWidget(deleteButton);
	rightLayout->addWidget(new QWidget(this), 1);
	mainLayout->addLayout(rightLayout);
	if (needFilter)
	{
		connect(classListView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(classSelected(const QItemSelection &, const QItemSelection &)));
		connect(treeDataPlugin, SIGNAL(dataCreated(Data *)), this, SLOT(classUpdated(Data *)));
		connect(treeDataPlugin, SIGNAL(dataUpdated(Data *)), this, SLOT(classUpdated(Data *)));
		connect(treeDataPlugin, SIGNAL(dataRemoved(Data *)), this, SLOT(classUpdated(Data *)));
	}
	connect(userListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(userSelected(const QModelIndex &, const QModelIndex &)));
	connect(userDataPlugin, SIGNAL(dataCreated(Data *)), this, SLOT(userUpdated(Data *)));
	connect(userDataPlugin, SIGNAL(dataUpdated(Data *)), this, SLOT(userUpdated(Data *)));
	connect(userDataPlugin, SIGNAL(dataRemoved(Data *)), this, SLOT(userUpdated(Data *)));
        connect(addButton, SIGNAL(clicked()), this, SLOT(attendanceAdded()));
        connect(editButton, SIGNAL(clicked()), this, SLOT(attendanceEdited()));
        connect(deleteButton, SIGNAL(clicked()), this, SLOT(attendanceDeleted()));
       // connect(userListView, SIGNAL(activated(const QModelIndex &)), this, SLOT(attendanceEdited()));
}

void					ListUser::showEvent(QShowEvent *)
{
	userListView->resizeColumnsToContents();
	userListView->resizeRowsToContents();
	userListView->horizontalHeader()->setStretchLastSection(true);
	if (userListView->currentIndex().isValid())
	{
		delete informations;
		informations = new InformationsUser(this, (UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->currentIndex())).internalPointer()));
		informationsLayout->addWidget(informations);
	}
}

void					ListUser::classSelected(const QItemSelection &selected, const QItemSelection &)
{
	if (selected.indexes().size() == 1)
		classFilter->setFilterRegExp(QRegExp("\\b" + QString::number(((TreeData *)(gradeFilter->mapToSource(selected.indexes().at(0)).internalPointer()))->id()) + "\\b"));
	else
		classFilter->setFilterRegExp(QRegExp(".*"));
	if (!userListView->currentIndex().isValid())
	{
                addButton->setDisabled(true);
		editButton->setDisabled(true);
		deleteButton->setDisabled(true);
	}
	userListView->update();
	userListView->resizeColumnsToContents();
	userListView->resizeRowsToContents();
	userListView->horizontalHeader()->setStretchLastSection(true);
}

void					ListUser::userSelected(const QModelIndex &current, const QModelIndex &)
{
	if (current.isValid() && current == userListView->currentIndex())
	{
                addButton->setDisabled(false);
		editButton->setDisabled(false);
		deleteButton->setDisabled(false);
		delete informations;
		informations = new InformationsUser(this, (UserData *)(userFilter->mapToSource(classFilter->mapToSource(current)).internalPointer()));
		informationsLayout->addWidget(informations);
	}
}

void					ListUser::attendanceAdded()
{
        if (userListView && userListView->selectionModel()->hasSelection())
        {
            TreeData *tmpNode = (TreeData *)(gradeFilter->mapToSource(classListView->selectionModel()->currentIndex()).internalPointer());
            if (tmpNode == 0)
                tmpNode = ((UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()))->studentClass();
            emit AddAttendance(tmpNode, (UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()));
        }
        else
                emit AddAttendance(0, 0);
}

void					ListUser::attendanceEdited()
{
        if (userListView && userListView->selectionModel()->hasSelection())
        {
                TreeData *tmpNode = (TreeData *)(gradeFilter->mapToSource(classListView->selectionModel()->currentIndex()).internalPointer());
                if (tmpNode == 0)
                    tmpNode = ((UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()))->studentClass();
                emit ShowAttendance(tmpNode, (UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()));
        }
                else
                emit ShowAttendance(0, (UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()));
}

void					ListUser::attendanceDeleted()
{
	QMessageBox			*confirm;
        int				ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + userListView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		((UserData *)(userFilter->mapToSource(classFilter->mapToSource(userListView->selectionModel()->currentIndex())).internalPointer()))->remove();
}

void					ListUser::classUpdated(Data *)
{
	if (!classListView)
		return ;
	classListView->update();
}

void					ListUser::userUpdated(Data *)
{
	if (classListView)
	{
		if (classListView->selectionModel()->selectedIndexes().size() == 1)
			classFilter->setFilterRegExp(QRegExp("\\b" + QString::number(((TreeData *)(gradeFilter->mapToSource(classListView->selectionModel()->selectedIndexes().at(0)).internalPointer()))->id()) + "\\b"));
		else
			classFilter->setFilterRegExp(QRegExp(".*"));
	}
	userListView->update();
	userListView->resizeColumnsToContents();
	userListView->resizeRowsToContents();
	userListView->horizontalHeader()->setStretchLastSection(true);
	if (userListView->model()->rowCount() && userListView->currentIndex().isValid())
	{
		editButton->setDisabled(false);
		deleteButton->setDisabled(false);
	}
	else
	{
		editButton->setDisabled(true);
		deleteButton->setDisabled(true);
	}
}
