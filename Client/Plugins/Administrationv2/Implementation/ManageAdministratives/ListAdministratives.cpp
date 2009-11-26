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
#include				"ListAdministratives.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

ListAdministratives::ListAdministratives(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
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
	listTitle = new QLabel(tr("Select a administrative to view or edit it."));
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	filter = new QSortFilterProxyModel(this);
	filter->setSourceModel(pluginManager->findPlugin<UserDataPlugin*>()->listModel());
	filter->setFilterRole(Data::FILTER_ROLE);
	filter->setFilterKeyColumn(0);
	filter->setFilterFixedString("ADMINISTRATOR");
	listView = new QListView(this);
	listView->setSelectionMode(QAbstractItemView::SingleSelection);
	listView->setDragEnabled(true);
	listView->setAcceptDrops(true);
	listView->setDropIndicatorShown(true);	listView->setModel(filter);
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
	displayer = new DisplayAdministrative(informationsFrame);
	informationsLayout->addWidget(displayer);
	rightLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	rightLayout->addWidget(actionsTitle);
	addButton = new QPushButton(QIcon(":/Icons/add-administrator.png"), tr("Add a administrative"), this);
	rightLayout->addWidget(addButton);
	editButton = new QPushButton(QIcon(":/Icons/edit-administrator.png"), tr("Edit this administrative"), this);
	editButton->setDisabled(true);
	rightLayout->addWidget(editButton);
	deleteButton = new QPushButton(QIcon(":/Icons/remove-administrator.png"), tr("Delete this administrative"), this);
	deleteButton->setDisabled(true);
	rightLayout->addWidget(deleteButton);
	rightLayout->addWidget(new QWidget(this), 1);
	mainLayout->addLayout(rightLayout);
	connect(listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(AdministrativeSelected(const QModelIndex &, const QModelIndex &)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(AdministrativeAdded()));
	connect(editButton, SIGNAL(clicked()), this, SLOT(AdministrativeEdited()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(AdministrativeDeleted()));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataCreated(Data *)), this, SLOT(AdministrativeUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataUpdated(Data *)), this, SLOT(AdministrativeUpdated(Data *)));
	connect(pluginManager->findPlugin<UserDataPlugin *>(), SIGNAL(dataRemoved(Data *)), this, SLOT(AdministrativeUpdated(Data *)));
}

void					ListAdministratives::AdministrativeSelected(const QModelIndex &current, const QModelIndex &)
{
	editButton->setDisabled(false);
	deleteButton->setDisabled(false);
	delete displayer;
	displayer = new DisplayAdministrative(this, (UserData*)(filter->mapToSource(current).internalPointer()));
	informationsLayout->addWidget(displayer);
}

void					ListAdministratives::AdministrativeAdded()
{
	emit editAdministrative(0);
}

void					ListAdministratives::AdministrativeEdited()
{
	emit editAdministrative((UserData*)(filter->mapToSource(listView->selectionModel()->currentIndex()).internalPointer()));
}

void					ListAdministratives::AdministrativeDeleted()
{
	QMessageBox			*confirm;
	int					ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + listView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		((UserData*)(filter->mapToSource(listView->selectionModel()->currentIndex()).internalPointer()))->remove();
}

void					ListAdministratives::AdministrativeUpdated(Data *)
{
	listView->update();
}
