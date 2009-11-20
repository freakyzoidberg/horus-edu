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
	filter = new QSortFilterProxyModel(this);
	filter->setSourceModel(pluginManager->findPlugin<UserDataPlugin*>()->model());
	filter->setFilterRole(Data::FILTER_ROLE);
	filter->setFilterKeyColumn(0);
	filter->setFilterFixedString("TEACHER");
	listView = new QListView(this);
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
