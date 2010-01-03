#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QList>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "studentslist.h"

StudentsList::StudentsList(TreeData *node, PluginManager  *pluginManager, QVBoxLayout *RightLayout)
{
	_pluginManager = pluginManager;
	_node = node;

	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	_sList = new QListWidget(this);
	_sList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a student to add, view or edit its grades."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(_sList);

//	connect(_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
	//		this, SLOT(selectStudents(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillExamsList()));
	this->setLayout(ListLayout);
}

void	StudentsList::fillStudentList()
{
	UserDataPlugin	*users = _pluginManager->findPlugin<UserDataPlugin *>();

	_sList->clear();
	QList<Data *> usersData = users->allDatas();
	for (int i = 0; i < usersData.size(); ++i)
	{
		UserData *data = qobject_cast<UserData *>(usersData.at(i));
		if (data->studentClass() == _node->parent())
		{
			QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"),
															data->name() + " " + data->surname());
			tempitem->setData(Qt::UserRole, data->id());
			_sList->addItem(tempitem);
		}
	}

	ExamsDataPlugin	*ep = _pluginManager->findPlugin<ExamsDataPlugin *>();
	_exam = ep->exam(_item->data(Qt::UserRole).toInt());
}

