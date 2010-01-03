#include "MarksExamsList.h"

MarksExamsList::MarksExamsList(PluginManager *pluginManager, QTabWidget *mainView)
{
	_parent = mainView;
	_pluginManager = pluginManager;
	_infosLabel = new QLabel();
	_formaddmark = NULL;

	td = pluginManager->findPlugin<TreeDataPlugin *>();

	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);
	_sList = new StudentsList(_node, pluginManager, RightLayout);
	_examsList = new ExamsList(pluginManager, RightLayout);
	_formAdd = new NewExams(RightLayout);

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
	RightLayout->addWidget(_infosLabel);
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
	RightLayout->addWidget(new QWidget(), 1);

	MainLayout->addWidget(_examsList);
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

	connect(_add, SIGNAL(clicked()), this, SLOT(addExam()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
	connect(back, SIGNAL(clicked()), this, SLOT(fallback()));
	connect(_examsList->_examsList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SLOT(viewStudentList(QListWidgetItem *)));
	connect(_sList->_sList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(studentSelection(QListWidgetItem *)));
	this->setLayout(MainLayout);
}

void MarksExamsList::addExam()
{
	this->MainLayout->removeWidget(_examsList);
	_examsList->setVisible(false);
	this->MainLayout->insertWidget(0, _formAdd);
	_formAdd->show();
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	back->setVisible(true);
	save->setVisible(true);
	_add->setVisible(false);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void	MarksExamsList::saveExam()
{
	ExamsDataPlugin	*examsPlugin = this->_pluginManager->findPlugin<ExamsDataPlugin *>();
	ExamsData *data = examsPlugin->newExams(_examsList->_node,
											this->_formAdd->examComment->text(),
											_pluginManager->currentUser());
	data->setDate(_formAdd->thedate->date());
	data->create();
	this->MainLayout->removeWidget(_formAdd);
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	_examsList->show();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	MainLayout->setStretch(0, 1);
	_examsList->Exams(_examsList->_node);
	if (_formaddmark)
	{
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}

}

void	MarksExamsList::fallback()
{
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	this->MainLayout->removeWidget(_formAdd);;
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_examsList->show();
	this->MainLayout->removeWidget(_sList);
	_sList->hide();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void MarksExamsList::viewStudentList(QListWidgetItem *item)
{
	quint32 exId = item->data(Qt::UserRole).toInt();
	ExamsDataPlugin	*examsPlugin = this->_pluginManager->findPlugin<ExamsDataPlugin *>();
	ExamsData *tmp = examsPlugin->exam(exId);

	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name()
						 + "\nExamination: " + tmp->comment());
	this->MainLayout->removeWidget(_examsList);
	_examsList->setVisible(false);
	this->MainLayout->insertWidget(0, _sList);
	_sList->setNode(_node);
	_sList->setItem(item);
	_sList->fillStudentList();
	_sList->show();
	_add->setVisible(false);
	back->setVisible(true);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void	MarksExamsList::studentSelection(QListWidgetItem *item)
{
	if (!_formaddmark)
		this->MainLayout->insertWidget(1, _formaddmark = new FormAddGrade());
}
