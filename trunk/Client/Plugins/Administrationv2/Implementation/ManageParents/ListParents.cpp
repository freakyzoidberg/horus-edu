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
#include				"ListParents.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

//#include				"ParentsModel.h"

ListParents::ListParents(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*leftLayout;
	QBoxLayout			*rightLayout;
	QFrame				*informationsFrame;
	QLabel				*informationsTitle;
	QLabel				*actionsTitle;
	QLabel				*listTitle;
	QPushButton			*addButton;
	QAbstractListModel	*parentsModel;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	listTitle = new QLabel(tr("Select a parent to view or edit it."));
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	listView = new QListView(this);
//	parentsModel = new ParentsModel(pluginManager->findPlugin<UserDataPlugin *>()->allUser(), this);
	listView->setModel(parentsModel);
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
	displayer = new DisplayParent(informationsFrame);
	informationsLayout->addWidget(displayer);
	rightLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	rightLayout->addWidget(actionsTitle);
	addButton = new QPushButton(QIcon(":/Icons/add-parents.png"), tr("Add a parent"), this);
	rightLayout->addWidget(addButton);
	editButton = new QPushButton(QIcon(":/Icons/edit-parents.png"), tr("Edit this parent"), this);
	editButton->setDisabled(true);
	rightLayout->addWidget(editButton);
	deleteButton = new QPushButton(QIcon(":/Icons/remove-parents.png"), tr("Delete this parent"), this);
	deleteButton->setDisabled(true);
	rightLayout->addWidget(deleteButton);
	rightLayout->addWidget(new QWidget(this), 1);
	mainLayout->addLayout(rightLayout);
	connect(listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(parentSelected(const QModelIndex &, const QModelIndex &)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(parentAdded()));
	connect(editButton, SIGNAL(clicked()), this, SLOT(parentEdited()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(parentDeleted()));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataCreated(Data *)), this, SLOT(ParentUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataUpdated(Data *)), this, SLOT(ParentUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataRemoved(Data *)), this, SLOT(ParentUpdated(Data *)));
}

void					ListParents::parentSelected(const QModelIndex &current, const QModelIndex &)
{
	editButton->setDisabled(false);
	deleteButton->setDisabled(false);
	delete displayer;
	displayer = new DisplayParent(this, _pluginManager->findPlugin<UserDataPlugin *>()->user(current.data(Qt::UserRole).toUInt()));
	informationsLayout->addWidget(displayer);
}

void					ListParents::parentAdded()
{
	emit editParent(0);
}

void					ListParents::parentEdited()
{
	emit editParent(_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt()));
}

void					ListParents::parentDeleted()
{
	QMessageBox			*confirm;
	int					ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + listView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt())->remove();
}

void					ListParents::ParentUpdated(Data *)
{
	listView->update();
	if (!listView->model()->rowCount())
	{
		editButton->setDisabled(true);
		deleteButton->setDisabled(true);
	}
	else
	{
		editButton->setDisabled(false);
		deleteButton->setDisabled(false);
	}
}
