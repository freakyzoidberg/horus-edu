#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "subjectlist.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "../../../../Common/ExamsData.h"

SubjectList::SubjectList(PluginManager *pluginManager)
{
	_pluginManager = pluginManager;
	this->treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	SubjectsList = new QListWidget(this);
	SubjectsList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a class to view, add or edit its time table."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(SubjectsList);

	connect(SubjectsList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(showExams(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillSubjectList()));
	this->setLayout(ListLayout);

	examComment = new QLineEdit();
	QPushButton	*addExam = new QPushButton("Add exam");

	connect(addExam, SIGNAL(clicked()), this, SLOT(addAnExam()));

	ListLayout->addWidget(examComment);
	ListLayout->addWidget(addExam);
	fillSubjectList();
}

QMap<int, QString> SubjectList::getallsubject()
{
	QMap<int, QString> allclass, exams;

	for (int i = 0; i < treePlugin->allDatas().size(); ++i)
	{
		TreeData    *data = qobject_cast<TreeData *>(treePlugin->allDatas().at(i));
		if ((data->type() == "SUBJECT") && IS_VALID_DATA_STATUS(data->status()))
			allclass.insert(data->id(), data->name());
	}


	ExamsDataPlugin *e = _pluginManager->findPlugin<ExamsDataPlugin *>();

	for (int i = 0; i < e->allDatas().size(); ++i)
	{
		qDebug() << "passage";

		ExamsData    *data = qobject_cast<ExamsData *>(e->allDatas().at(i));
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"), data->comment());
		tempitem->setData(Qt::UserRole, data->teacher());
		SubjectsList->addItem(tempitem);

		//allclass.insert(data->id(), data->name());
	}

	return allclass;
}

void	SubjectList::fillSubjectList()
{
	QMapIterator<int, QString> i(getallsubject());
	SubjectsList->clear();

	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"), i.value());
		tempitem->setData(Qt::UserRole, i.key());
		SubjectsList->addItem(tempitem);
	}
}

void SubjectList::showExams(QListWidgetItem *item)
{
	qDebug() << "clicked";
}

void SubjectList::addAnExam()
{
	qDebug() << "added";

	ExamsDataPlugin *test = this->_pluginManager->findPlugin<ExamsDataPlugin *>();


	 ExamsData *ex =
			 test->newExams(_pluginManager->currentUser()->studentClass(),
								  this->examComment->text() , _pluginManager->currentUser());

	ex->setTeacher(2);
	ex->setDate(QDate().currentDate());
	ex->setComment(this->examComment->text());
	ex->create();
 }

