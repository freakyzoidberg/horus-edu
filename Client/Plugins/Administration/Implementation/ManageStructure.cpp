#include				"ManageStructure.h"

#include				<QFrame>
#include				<QLabel>

#include				"ElementSchool.h"
#include				"ElementClass.h"
#include				"StructureForm.h"

ManageStructure::ManageStructure(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin) : QWidget(parent)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*panelLayout;
	QFrame				*informationsFrame;
	QLabel				*informationsTitle;
	QBoxLayout			*informationsLayout;
	QLabel				*actionsTitle;
	StructureForm		*form;

	addSchoolButton = new QPushButton(QIcon(":/Icons/add-school.png"), tr("Add a school"), this);
	editSchoolButton = new QPushButton(QIcon(":/Icons/edit-school.png"), tr("Edit a school"), this);
	removeSchoolButton = new QPushButton(QIcon(":/Icons/remove-school.png"), tr("Delete a school"), this);
	addClassButton = new QPushButton(QIcon(":/Icons/add-desk.png"), tr("Add a class"), this);
	editClassButton = new QPushButton(QIcon(":/Icons/edit-desk.png"), tr("Edit a class"), this);
	removeClassButton = new QPushButton(QIcon(":/Icons/remove-desk.png"), tr("Delete a class"), this);
	addSubjectButton = new QPushButton(QIcon(":/Icons/add-subject.png"), tr("Add a subject"), this);
	editSubjectButton = new QPushButton(QIcon(":/Icons/edit-subject.png"), tr("Edit a subject"), this);
	removeSubjectButton = new QPushButton(QIcon(":/Icons/remove-subject.png"), tr("Delete a subject"), this);
	addSchoolButton->setDisabled(true);
	addClassButton->setDisabled(true);
	addSubjectButton->setDisabled(true);
	editSchoolButton->setDisabled(true);
	editClassButton->setDisabled(true);
	editSubjectButton->setDisabled(true);
	removeSchoolButton->setDisabled(true);
	removeClassButton->setDisabled(true);
	removeSubjectButton->setDisabled(true);
	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	leftLayout = new QBoxLayout(QBoxLayout::BottomToTop);
	mainLayout->addLayout(leftLayout, 1);
	form = new StructureForm(this, userDataPlugin);
	leftLayout->addWidget(form);
	form->hide();
	leftLayout->addWidget(new QWidget(this), 1);
	classes = new ElementClass(this, treeDataPlugin);
	connect(classes, SIGNAL(enabled()), this, SLOT(classEnabled()));
	connect(classes, SIGNAL(disabled()), this, SLOT(classDisabled()));
	classes->update();
	classes->setForm(form);
	leftLayout->addWidget(classes);
	school = new ElementSchool(this, treeDataPlugin, userDataPlugin);
	connect(school, SIGNAL(enabled()), this, SLOT(schoolEnabled()));
	connect(school, SIGNAL(disabled()), this, SLOT(schoolDisabled()));
	school->update();
	school->setForm(form);
	leftLayout->addWidget(school);
	panelLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(panelLayout);
    panelLayout->setMargin(0);
    panelLayout->setSpacing(2);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
    informationsLayout->setSpacing(0);
    informationsLayout->setMargin(0);
	informationsFrame->setMinimumWidth(200);
	informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
    informationsTitle->setProperty("isTitle", true);
    informationsTitle->setProperty("isRound", true);
	informationsLayout->addWidget(informationsTitle);
	//informations = new InformationsUser(informationsFrame);
	//informationsLayout->addWidget(informations);
	panelLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	panelLayout->addWidget(actionsTitle);
	panelLayout->addWidget(addSchoolButton);
	panelLayout->addWidget(editSchoolButton);
	panelLayout->addWidget(removeSchoolButton);
	panelLayout->addWidget(addClassButton);
	panelLayout->addWidget(editClassButton);
	panelLayout->addWidget(removeClassButton);
	panelLayout->addWidget(addSubjectButton);
	panelLayout->addWidget(editSubjectButton);
	panelLayout->addWidget(removeSubjectButton);
	panelLayout->addWidget(new QWidget(this), 1);
	connect(addSchoolButton, SIGNAL(clicked()), school, SLOT(add()));
	connect(editSchoolButton, SIGNAL(clicked()), school, SLOT(edit()));
	connect(removeSchoolButton, SIGNAL(clicked()), school, SLOT(remove()));
	connect(addClassButton, SIGNAL(clicked()), classes, SLOT(add()));
	connect(editClassButton, SIGNAL(clicked()), classes, SLOT(edit()));
	connect(removeClassButton, SIGNAL(clicked()), classes, SLOT(remove()));
}

void					ManageStructure::schoolEnabled()
{
	addSchoolButton->setDisabled(true);
	editSchoolButton->setDisabled(false);
	removeSchoolButton->setDisabled(false);
	addClassButton->setDisabled(false);
	classes->show();
}

void					ManageStructure::schoolDisabled()
{
	addSchoolButton->setDisabled(false);
	editSchoolButton->setDisabled(true);
	removeSchoolButton->setDisabled(true);
	addClassButton->setDisabled(true);
	classes->hide();
}

void					ManageStructure::classEnabled()
{
	editClassButton->setDisabled(false);
	removeClassButton->setDisabled(false);
	addSubjectButton->setDisabled(false);
}

void					ManageStructure::classDisabled()
{
	editClassButton->setDisabled(true);
	removeClassButton->setDisabled(true);
	addSubjectButton->setDisabled(true);
}
