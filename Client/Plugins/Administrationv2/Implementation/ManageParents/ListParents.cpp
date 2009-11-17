#include				"ListParents.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

#include				"ParentsModel.h"

ListParents::ListParents(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*rightLayout;
	QBoxLayout			*actionsMainLayout;
	QBoxLayout			*actionsBottomLayout;
	QFrame				*informationsFrame;
	QFrame				*actionsFrame;
	QLabel				*informationsTitle;
	QLabel				*actionsTitle;
	QPushButton			*addButton;
	QAbstractListModel	*parentsModel;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	listView = new QListView(this);
	parentsModel = new ParentsModel(pluginManager->findPlugin<UserDataPlugin *>()->allUser(), this);
	listView->setModel(parentsModel);
	mainLayout->addWidget(listView);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
	informationsTitle = new QLabel(tr("Informations"), this);
	informationsLayout->addWidget(informationsTitle);
	displayer = new DisplayParent(this);
	informationsLayout->addWidget(displayer);
	rightLayout->addWidget(informationsFrame, 0, Qt::AlignTop);
	actionsFrame = new QFrame(this);
	actionsFrame->setMinimumWidth(200);
	actionsMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, actionsFrame);
	actionsTitle = new QLabel(tr("Actions"), this);
	actionsMainLayout->addWidget(actionsTitle);
	actionsBottomLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	addButton = new QPushButton(QIcon(":/Icons/add-parents.png"), tr("Add"), actionsFrame);
	actionsBottomLayout->addWidget(addButton);
	editButton = new QPushButton(QIcon(":/Icons/edit-parents.png"), tr("Edit"), actionsFrame);
	editButton->setDisabled(true);
	actionsBottomLayout->addWidget(editButton);
	deleteButton = new QPushButton(QIcon(":/Icons/remove-parents.png"), tr("Delete"), actionsFrame);
	deleteButton->setDisabled(true);
	actionsBottomLayout->addWidget(deleteButton);
	actionsMainLayout->addLayout(actionsBottomLayout);
	rightLayout->addWidget(actionsFrame, 0, Qt::AlignBottom);
	mainLayout->addLayout(rightLayout);
	connect(listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(parentSelected(const QModelIndex &, const QModelIndex &)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(parentAdded()));
	connect(editButton, SIGNAL(clicked()), this, SLOT(parentEdited()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(parentDeleted()));
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
