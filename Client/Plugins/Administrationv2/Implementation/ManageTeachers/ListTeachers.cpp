#include				"ListTeachers.h"

#include				<QFrame>
#include				<QLabel>
#include				<QMessageBox>

#include				"TeachersModel.h"

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
	QAbstractListModel	*teachersModel;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(2);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	listTitle = new QLabel(tr("Select a teacher to view or edit it."));
	listTitle->setProperty("isTitle", true);
	leftLayout->addWidget(listTitle);
	listView = new QListView(this);
	teachersModel = new TeachersModel(pluginManager->findPlugin<UserDataPlugin *>()->allUser(), this);
	listView->setModel(teachersModel);
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
}

void					ListTeachers::TeacherSelected(const QModelIndex &current, const QModelIndex &)
{
	editButton->setDisabled(false);
	deleteButton->setDisabled(false);
	delete displayer;
	displayer = new DisplayTeacher(this, _pluginManager->findPlugin<UserDataPlugin *>()->user(current.data(Qt::UserRole).toUInt()));
	informationsLayout->addWidget(displayer);
}

void					ListTeachers::TeacherAdded()
{
	emit editTeacher(0);
}

void					ListTeachers::TeacherEdited()
{
	emit editTeacher(_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt()));
}

void					ListTeachers::TeacherDeleted()
{
	QMessageBox			*confirm;
	int					ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + listView->selectionModel()->currentIndex().data().toString() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		_pluginManager->findPlugin<UserDataPlugin *>()->user(listView->selectionModel()->currentIndex().data(Qt::UserRole).toUInt())->remove();
}
