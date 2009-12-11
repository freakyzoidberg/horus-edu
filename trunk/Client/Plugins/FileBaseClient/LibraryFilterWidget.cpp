#include "LibraryFilterWidget.h"
#include "LibraryFilterProxyModel.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/UserData.h"
#include <QFormLayout>
#include <QComboBox>
#include <QSortFilterProxyModel>

LibraryFilterWidget::LibraryFilterWidget(PluginManager* pluginManager, LibraryFilterProxyModel* filter, QWidget *parent) : QWidget(parent)
{
	_treeDataPlugin = pluginManager->findPlugin<TreeDataPlugin*>();
	_userDataPlugin = pluginManager->findPlugin<UserDataPlugin*>();
	_filter = filter;

	QFormLayout* layout = new QFormLayout(this);

	_filter->nodeListChanged(_treeDataPlugin->allDatas());

	grades.addItem(tr("All"), 0);
	foreach (TreeData* node, _treeDataPlugin->grades())
		grades.addItem(node->icon(), node->name(), node->id());
	connect(&grades, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	layout->addRow("Grades:",  &grades);

	subjects.addItem(tr("All"));
	subjects.addItems(_treeDataPlugin->subjects());
	connect(&subjects, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	layout->addRow("Subject:", &subjects);

	owners.addItem(tr("All"), -1);
	owners.addItem(tr("Nobody"), 0);
	foreach (Data* data, _userDataPlugin->allDatas())
	{
		UserData* user = static_cast<UserData*>(data);
		if (user->level() <= LEVEL_TEACHER)
			owners.addItem(user->icon(), user->name() + ' ' + user->surname(), user->id());
	}
	connect(&owners, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	layout->addRow("Owner:",   &owners);
}

void LibraryFilterWidget::comboBoxChanged(int)
{
	QList<Data*> list;
	foreach (Data* data, _treeDataPlugin->allDatas())
	{
		TreeData* node = static_cast<TreeData*>(data);
		quint32 gradeId = grades.itemData(grades.currentIndex()).toUInt();
		QString subject = subjects.currentText();
		quint32 ownerId = owners.itemData(owners.currentIndex()).toUInt();

		bool isValid = true;

		if (gradeId && node->id() != gradeId)
			isValid = false;

		if (subject != tr("All") && node->name() != subject)
			isValid = false;

		if (ownerId != -1 && node->user()->id() == ownerId)
			isValid = false;

		if (isValid)
			list.append(node);
	}

	_filter->nodeListChanged(list);
}
