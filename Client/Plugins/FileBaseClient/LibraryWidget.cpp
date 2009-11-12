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
#include <QLabel>
#include <QCheckBox>

LibraryWidget::LibraryWidget(PluginManager* pluginManager)
{
	QGridLayout* layout = new QGridLayout(this);

	QTreeView* tree = new QTreeView(this);
	tree->setModel(new TreeModel(pluginManager->findPlugin<TreeDataPlugin*>()));
	tree->expandAll();
	tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tree->selectAll();
	tree->setHeaderHidden(true);
	_treeSelection = tree->selectionModel();
	connect(_treeSelection, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(treeSelectionChange(QItemSelection,QItemSelection)));

	_filter = new QSortFilterProxyModel(this);
	_filter->setSourceModel(new LibraryModel(pluginManager->findPlugin<FileDataPlugin*>()));
	_filter->setSortCaseSensitivity(Qt::CaseInsensitive);
	_filter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	_filter->sort(0, Qt::AscendingOrder);

	QListView* list = new QListView(this);
	list->setModel(_filter);

	QLineEdit* matchLine = new QLineEdit;
	connect(matchLine, SIGNAL(textChanged(QString)), _filter, SLOT(setFilterRegExp(QString)));

	layout->setColumnStretch(0, 2);
	layout->setColumnStretch(1, 0);
	layout->setColumnStretch(2, 6);
	layout->setColumnStretch(3, 3);

	layout->addWidget(new QLabel(tr("Into Directory")), 0, 0);
	layout->addWidget(tree, 1, 0);

	layout->addWidget(new QLabel(tr("Search")), 0, 1);
	layout->addWidget(matchLine, 0, 2);

	layout->addWidget(list, 1, 1, 1, 2);

	layout->addWidget(new QLabel(tr("Information")), 0, 3);
}

void LibraryWidget::treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected)
{
}
