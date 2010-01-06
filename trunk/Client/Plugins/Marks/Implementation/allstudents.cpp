#include "allstudents.h"
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"

#include <QLabel>

AllStudents::AllStudents(PluginManager *pluginManager)
{
	_pluginManager = pluginManager;

	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	_sList = new QListWidget(this);
	_sList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Selectionner un etudiant pour voir ses notes."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(_sList);

//	connect(_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
	//		this, SLOT(selectStudents(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillExamsList()));
	this->setLayout(ListLayout);
}

void	AllStudents::fillList()
{
	UserDataPlugin	*users = _pluginManager->findPlugin<UserDataPlugin *>();

	for (int i = 0; i < users->allDatas().size(); ++i)
	{
		UserData *tmp = qobject_cast<UserData *>(users->allDatas().at(i));
		if (tmp->level() == LEVEL_STUDENT)
		{
			QListWidgetItem * userInList = new QListWidgetItem(QIcon(":/administrator.png"), tmp->name() + " " + tmp->surname());
			userInList->setData(Qt::UserRole, QVariant(tmp->id()));
			_sList->addItem(userInList);
		}
	}
}
