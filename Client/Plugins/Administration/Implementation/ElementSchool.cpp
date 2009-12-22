#include		"ElementSchool.h"

#include		<QBoxLayout>
#include		<QPixmap>

#include		"../../../../Common/TreeData.h"

ElementSchool::ElementSchool(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin) : StructureElement(parent, treeDataPlugin)
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*columnLayout;
	QLabel		*picture;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	picture = new QLabel(this);
	picture->setPixmap(QPixmap(":/Icons/school.png"));
	columnLayout->addWidget(picture);
	name = new QLabel(this);
	columnLayout->addWidget(name);
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	columnLayout->addWidget(new QLabel(tr("Students number"), this));
	columnLayout->addWidget(new QLabel(tr("Parents number"), this));
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	studentsNumber = new QLabel(this);
	columnLayout->addWidget(studentsNumber);
	parentsNumber = new QLabel(this);
	columnLayout->addWidget(parentsNumber);
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	columnLayout->addWidget(new QLabel(tr("Teachers number"), this));
	columnLayout->addWidget(new QLabel(tr("Administratives number"), this));
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	teachersNumber = new QLabel(this);
	columnLayout->addWidget(teachersNumber);
	administrativesNumber = new QLabel(this);
	columnLayout->addWidget(administrativesNumber);
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	columnLayout->addWidget(new QLabel(tr("Classes number"), this));
	columnLayout->addWidget(new QLabel(tr("Users number"), this));
	columnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(columnLayout);
	classesNumber = new QLabel(this);
	columnLayout->addWidget(classesNumber);
	usersNumber = new QLabel(this);
	columnLayout->addWidget(usersNumber);
	mainLayout->addWidget(new QWidget(this), 1);
	studentsModel = new QSortFilterProxyModel(this);
	studentsModel->setSourceModel(userDataPlugin->listModel());
	studentsModel->setFilterRole(Data::FILTER_ROLE);
	studentsModel->setFilterKeyColumn(0);
	studentsModel->setFilterFixedString("STUDENT");
	parentsModel = new QSortFilterProxyModel(this);
	parentsModel->setSourceModel(userDataPlugin->listModel());
	parentsModel->setFilterRole(Data::FILTER_ROLE);
	parentsModel->setFilterKeyColumn(0);
	parentsModel->setFilterFixedString("FAMILY");
	teachersModel = new QSortFilterProxyModel(this);
	teachersModel->setSourceModel(userDataPlugin->listModel());
	teachersModel->setFilterRole(Data::FILTER_ROLE);
	teachersModel->setFilterKeyColumn(0);
	teachersModel->setFilterFixedString("TEACHER");
	administrativesModel = new QSortFilterProxyModel(this);
	administrativesModel->setSourceModel(userDataPlugin->listModel());
	administrativesModel->setFilterRole(Data::FILTER_ROLE);
	administrativesModel->setFilterKeyColumn(0);
	administrativesModel->setFilterFixedString("ADMINISTRATOR");
	classesModel = new QSortFilterProxyModel(this);
	classesModel->setSourceModel(treeDataPlugin->listModel());
	classesModel->setFilterRole(Qt::DisplayRole);
	classesModel->setFilterKeyColumn(1);
	classesModel->setDynamicSortFilter(true);
	classesModel->setFilterFixedString("GRADE");
	usersModel = userDataPlugin->listModel();
	connect(treeDataPlugin, SIGNAL(dataCreated(Data *)), this, SLOT(treeUpdated()));
	connect(treeDataPlugin, SIGNAL(dataUpdated(Data *)), this, SLOT(treeUpdated()));
	connect(treeDataPlugin, SIGNAL(dataRemoved(Data *)), this, SLOT(treeUpdated()));
	connect(userDataPlugin, SIGNAL(dataCreated(Data *)), this, SLOT(userUpdated()));
	connect(userDataPlugin, SIGNAL(dataUpdated(Data *)), this, SLOT(userUpdated()));
	connect(userDataPlugin, SIGNAL(dataRemoved(Data *)), this, SLOT(userUpdated()));
}

void			ElementSchool::update()
{
	treeUpdated();
	userUpdated();
}

void			ElementSchool::editElement()
{
	_form->setTitle(tr("School informations"));
	_form->setTeacherVisibility(true);
	if (_treeDataPlugin->rootNode()->status() != Data::EMPTY && _treeDataPlugin->rootNode()->status() < Data::REMOVED && _treeDataPlugin->rootNode()->status() != Data::REMOVING)
		_form->setName(_treeDataPlugin->rootNode()->name());
}

void			ElementSchool::removeElement()
{
	if (_treeDataPlugin->rootNode()->status() != Data::EMPTY && _treeDataPlugin->rootNode()->status() < Data::REMOVED && _treeDataPlugin->rootNode()->status() != Data::REMOVING)
		_treeDataPlugin->rootNode()->remove();
}

void			ElementSchool::validateElement()
{
	TreeData	*rootNode;

	rootNode = _treeDataPlugin->rootNode();
	rootNode->setName(_form->getName());
	rootNode->setType("ROOT");
	rootNode->setParent(rootNode);
	if (_treeDataPlugin->rootNode()->status() == Data::EMPTY || _treeDataPlugin->rootNode()->status() >= Data::REMOVED || _treeDataPlugin->rootNode()->status() == Data::REMOVING)
		rootNode->create();
	else
		rootNode->save();
}

void			ElementSchool::treeUpdated()
{
	if (_treeDataPlugin->rootNode()->status() == Data::EMPTY || _treeDataPlugin->rootNode()->status() >= Data::REMOVED || _treeDataPlugin->rootNode()->status() == Data::REMOVING)
	{
		if (!this->isHidden())
			this->hide();
		emit disabled();
	}
	else
	{
		qWarning() << _treeDataPlugin->rootNode()->status();
		if (this->isHidden())
			this->show();
		emit enabled();
		name->setText(_treeDataPlugin->rootNode()->name());
		classesNumber->setNum(classesModel->rowCount());
	}
}

void			ElementSchool::userUpdated()
{
	studentsNumber->setNum(studentsModel->rowCount());
	parentsNumber->setNum(parentsModel->rowCount());
	teachersNumber->setNum(teachersModel->rowCount());
	administrativesNumber->setNum(administrativesModel->rowCount());
	usersNumber->setNum(usersModel->rowCount());
}
