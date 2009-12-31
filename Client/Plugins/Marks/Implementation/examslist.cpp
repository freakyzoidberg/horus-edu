#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "examslist.h"

#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "../../../../Common/ExamsData.h"

ExamsList::ExamsList(PluginManager *pluginManager)
{
	_pluginManager = pluginManager;
	this->treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	_examsList = new QListWidget(this);
	_examsList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a subject to view, add or edit an exam."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(_examsList);

	connect(_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(showExams(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillExamsList()));
	this->setLayout(ListLayout);

	fillExamsList();
}

QMap<int, QString> ExamsList::getallexams()
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
		_examsList->addItem(tempitem);

		allclass.insert(data->id(), data->comment());
	}

	return allclass;
}

void	ExamsList::fillExamsList()
{
	QMapIterator<int, QString> i(getallexams());
	_examsList->clear();

	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"), i.value());
		tempitem->setData(Qt::UserRole, i.key());
		_examsList->addItem(tempitem);
	}
}

void ExamsList::showExams(QListWidgetItem *item)
{
	int subj;
	TreeData *mat;

	qDebug() << "clicked";

	subj = item->data(Qt::UserRole).toInt();

	ExamsDataPlugin *test = this->_pluginManager->findPlugin<ExamsDataPlugin *>();

	mat = treePlugin->node(subj);
}

void ExamsList::addAnExam()
{
	qDebug() << "added";


 }

