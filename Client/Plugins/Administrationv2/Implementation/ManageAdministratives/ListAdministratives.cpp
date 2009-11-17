#include				"ListAdministratives.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

#include				"AdministrativesModel.h"

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
	QAbstractListModel	*administrativesModel;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	listTitle = new QLabel(tr("Select a administrative to view or edit it."));
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	listView = new QListView(this);
	administrativesModel = new AdministrativesModel(pluginManager->findPlugin<UserDataPlugin *>()->allUser(), this);
	listView->setModel(administrativesModel);
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
}

void					ListAdministratives::AdministrativeSelected(const QModelIndex &current, const QModelIndex &)
{
	editButton->setDisabled(false);
	deleteButton->setDisabled(false);
	delete displayer;
	displayer = new DisplayAdministrative(this, _pluginManager->findPlugin<UserDataPlugin *>()->user(current.data(Qt::UserRole).toUInt()));
	informationsLayout->addWidget(displayer);
}

void					ListAdministratives::AdministrativeAdded()
{
	emit editAdministrative(0);
}

void					ListAdministratives::AdministrativeEdited()
{
	emit editAdministrative(_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt()));
}

void					ListAdministratives::AdministrativeDeleted()
{
	QMessageBox			*confirm;
	int					ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + listView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt())->remove();
}