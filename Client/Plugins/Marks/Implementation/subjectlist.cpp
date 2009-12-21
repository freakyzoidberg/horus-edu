#include <QVBoxLayout>
#include <QLabel>

#include "subjectlist.h"
#include "../../../../Common/TreeData.h"

SubjectList::SubjectList(PluginManager *pluginManager)
{
	this->treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	ClassList = new QListWidget(this);
	ClassList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a class to view, add or edit its time table."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(ClassList);

	   //connect(ClassList, SIGNAL(itemClicked(QListWidgetItem *)),
				//this, SLOT(updatestudents(QListWidgetItem *)));
			//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillClassList()));
	this->setLayout(ListLayout);

	fillClassList();
}

QMap<int, QString> SubjectList::getallclass()
{
	QMap<int, QString> allclass;

	for (int i = 0; i < treePlugin->allDatas().size(); ++i)
	{
		TreeData    *data = qobject_cast<TreeData *>(treePlugin->allDatas().at(i));
		if ((data->type() == "SUBJECT") && IS_VALID_DATA_STATUS(data->status()))
			allclass.insert(data->id(), data->name());
	}
	return allclass;
}

void	SubjectList::fillClassList()
{
	QMapIterator<int, QString> i(getallclass());
	ClassList->clear();

	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"), i.value());
		tempitem->setData(Qt::UserRole, i.key());
		ClassList->addItem(tempitem);
	}
}
