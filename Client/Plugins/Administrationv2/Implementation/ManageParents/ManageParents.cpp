#include				"ManageParents.h"

#include				<QBoxLayout>
#include				<QFrame>
#include				<QLabel>

#include				"../../../../../Common/PluginManager.h"
#include				"ParentsModel.h"

ManageParents::ManageParents(QWidget *parent, PluginManager *pluginManager) : QWidget(parent)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*rightLayout;
	QBoxLayout			*informationsLayout;
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

void					ManageParents::parentSelected(const QModelIndex &current, const QModelIndex &)
{
	editButton->setDisabled(false);
	deleteButton->setDisabled(false);
}

void					ManageParents::parentAdded()
{
}

void					ManageParents::parentEdited()
{
}

void					ManageParents::parentDeleted()
{
}
