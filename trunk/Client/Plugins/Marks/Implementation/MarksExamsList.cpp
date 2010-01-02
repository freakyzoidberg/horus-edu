#include "MarksExamsList.h"

MarksExamsList::MarksExamsList(PluginManager *pluginManager, QTabWidget *mainView)
{
	_formAdd = new NewExams();
	_parent = mainView;
	_pluginManager = pluginManager;

	//infos = NULL;
	td = pluginManager->findPlugin<TreeDataPlugin *>();

	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);

	_examsList = new ExamsList(pluginManager);
	QLabel *infoTitle = new QLabel(tr("Informations:"));
	infoTitle->setProperty("isTitle", true);
	infoTitle->setProperty("isRound", true);
	informationsFrame = new QFrame(this);
	informationsFrame->setMinimumWidth(200);

	informationsLayout = new QVBoxLayout(informationsFrame);
	informationsLayout->setSpacing(0);
	informationsLayout->setMargin(0);
	informationsLayout->addWidget(infoTitle);
	RightLayout->addWidget(informationsFrame);
	QLabel *actionTitle = new QLabel(tr("Actions:"));
	actionTitle->setProperty("isTitle", true);
	actionTitle->setProperty("isRound", true);

	del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete this edt"));
	edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit this edt"));
	ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/save.png"), tr("Apply"));
	reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/back.png"), tr("Cancel"));
	_add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Add"));

	RightLayout->addWidget(actionTitle);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(_add);
	RightLayout->addWidget(new QWidget(this), 1);

	MainLayout->addWidget(_examsList);
	//MainLayout->addWidget(_formAdd);
	MainLayout->addWidget(new QWidget());
	MainLayout->addLayout(RightLayout);
	MainLayout->setStretch(0, 1);

	ok->setVisible(false);
	save->setVisible(false);
	_add->setVisible(false);
	_formAdd->setVisible(false);
	reset->setVisible(false);
	back->setVisible(false);
	edit->setVisible(false);
	del->setVisible(false);

	//connect(AdmClassList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)),
	//	this, SLOT(classSelected(QListWidgetItem *)));
//	connect(_classList->Classlist, SIGNAL(itemClicked(QListWidgetItem *)),
	//		this, SLOT(subjectSelected(QListWidgetItem *)));
	//connect(_classList->Classlist, SIGNAL(itemDoubleClicked ( QListWidgetItem *)),
		//	this, SLOT(moveToExamList( QListWidgetItem *)));
	connect(_add, SIGNAL(clicked()), this, SLOT(addExam()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
	connect(back, SIGNAL(clicked()), this, SLOT(fallback()));
	this->setLayout(MainLayout);

}

void MarksExamsList::addExam()
{
	this->MainLayout->removeWidget(_examsList);;
	_examsList->setVisible(false);
	this->MainLayout->insertWidget(0, _formAdd);
	_formAdd->show();
	back->setVisible(true);
	save->setVisible(true);
	_add->setVisible(false);
	MainLayout->setStretch(0, 1);
}

void	MarksExamsList::saveExam()
{
	ExamsDataPlugin	*examsPlugin = this->_pluginManager->findPlugin<ExamsDataPlugin *>();
	ExamsData *data = examsPlugin->newExams(_examsList->_node,
											this->_formAdd->examComment->text(),
											_pluginManager->currentUser());
	data->setDate(_formAdd->thedate->date());
	data->create();

	this->MainLayout->removeWidget(_formAdd);;
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_examsList->show();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	MainLayout->setStretch(0, 1);
	_examsList->Exams(_examsList->_node);
}

void	MarksExamsList::fallback()
{
	this->MainLayout->removeWidget(_formAdd);;
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_examsList->show();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	MainLayout->setStretch(0, 1);
}
