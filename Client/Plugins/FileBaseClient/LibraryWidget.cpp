#include "LibraryWidget.h"

#include "LibraryModel.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/FileDataPlugin.h"
#include "../../../Common/TreeDataPlugin.h"

#include <QListView>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include <QGridLayout>
#include <QLineEdit>

LibraryWidget::LibraryWidget(PluginManager* pluginManager)
{
	QGridLayout* layout = new QGridLayout(this);

	QTreeView* tree = new QTreeView(this);
	tree->setModel(new TreeModel(pluginManager->findPlugin<TreeDataPlugin*>()));

	QSortFilterProxyModel* filter = new QSortFilterProxyModel(this);
	filter->setSourceModel(new LibraryModel(pluginManager->findPlugin<FileDataPlugin*>()));
	filter->setSortCaseSensitivity(Qt::CaseInsensitive);
	filter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filter->sort(0, Qt::AscendingOrder);

	QListView* list = new QListView(this);
	list->setModel(filter);

	QLineEdit* matchLine = new QLineEdit;
	connect(matchLine, SIGNAL(textChanged(QString)), filter, SLOT(setFilterRegExp(QString)));

	layout->addWidget(tree, 1, 0);
	layout->addWidget(matchLine, 0, 1);
	layout->addWidget(list, 1, 1);

}
