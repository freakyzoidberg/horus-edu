#include "LibraryFilterWidget.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/UserData.h"
#include <QFormLayout>
#include <QComboBox>
#include <QSortFilterProxyModel>

LibraryFilterWidget::LibraryFilterWidget(PluginManager* pluginManager, QWidget *parent) : QWidget(parent)
{

	_treeDataPlugin = pluginManager->findPlugin<TreeDataPlugin*>();
	_userDataPlugin = pluginManager->findPlugin<UserDataPlugin*>();

	updateFilters();

	QFormLayout* layout = new QFormLayout(this);
	layout->addRow("Grades:",  &grades);
	layout->addRow("Subject:", &subjects);
	layout->addRow("Owner:",   &owners);
}


void LibraryFilterWidget::updateFilters(Data*)
{
	grades.clear();
	grades.addItem(tr("All"), 0);
	foreach (TreeData* node, _treeDataPlugin->grades())
		grades.addItem(node->icon(), node->name(), node->id());

	subjects.clear();
	subjects.addItem(tr("All"));
	subjects.addItems(_treeDataPlugin->subjects());

	owners.clear();
	owners.addItem(tr("All"), 0);
	foreach (Data* data, _userDataPlugin->allDatas())
	{
		UserData* user = static_cast<UserData*>(data);
		if (user->level() <= LEVEL_TEACHER)
			owners.addItem(user->icon(), user->name() + ' ' + user->surname(), user->id());
	}
}
