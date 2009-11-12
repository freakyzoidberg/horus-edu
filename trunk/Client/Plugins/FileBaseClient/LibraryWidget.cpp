#include "LibraryWidget.h"

#include "LibraryModel.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/FileData.h"
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
	TreeModel* treeModel = new TreeModel(pluginManager->findPlugin<TreeDataPlugin*>());
	tree->setModel(treeModel);
	tree->expandAll();
	tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tree->selectAll();
	tree->setHeaderHidden(true);
	_treeSelection = tree->selectionModel();
	connect(_treeSelection, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(treeSelectionChange(QItemSelection,QItemSelection)));

	_filter = new LibrarySortFilter(treeModel, this);
	_filter->setSourceModel(new LibraryModel(pluginManager->findPlugin<FileDataPlugin*>()));
	_filter->setSortCaseSensitivity(Qt::CaseInsensitive);
	_filter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	_filter->sort(0, Qt::AscendingOrder);

	QListView* list = new QListView(this);
	list->setModel(_filter);
	list->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(list->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(fileSelectionChange(QItemSelection,QItemSelection)));

	QLineEdit* matchLine = new QLineEdit;
	connect(matchLine, SIGNAL(textChanged(QString)), _filter, SLOT(setFilterRegExp(QString)));

	_detailLayout = new QFormLayout;

	layout->setColumnStretch(0, 2);
	layout->setColumnStretch(1, 6);
	layout->setColumnStretch(2, 3);

	layout->addWidget(new QLabel(tr("Into Directory")), 0, 0);
	layout->addWidget(tree, 1, 0);

	layout->addWidget(matchLine, 0, 1);

	layout->addWidget(list, 1, 1);

	layout->addWidget(new QLabel(tr("Detail")), 0, 2);
	layout->addLayout(_detailLayout, 1, 2);

	_detailLayout->addRow("Id", new QLabel);
	_detailLayout->addRow("Name", new QLabel);
	_detailLayout->addRow("Size", new QLabel);
	_detailLayout->addRow("MimeType", new QLabel);
}

void LibraryWidget::treeSelectionChange(const QItemSelection& selected, const QItemSelection&)
{
//	foreach (QModelIndex index, selected.indexes())
//		for (int i=0; i < index.model()->rowCount(index); i++)
//			_treeSelection->select(index.child(i, 0), QItemSelectionModel::Select);
}

void LibraryWidget::fileSelectionChange(const QItemSelection& selected, const QItemSelection&)
{
	if ( ! selected.count())
	{
		((QLabel*)(_detailLayout->itemAt(0, QFormLayout::FieldRole)->widget()))->setText("");
		((QLabel*)(_detailLayout->itemAt(1, QFormLayout::FieldRole)->widget()))->setText("");
		((QLabel*)(_detailLayout->itemAt(2, QFormLayout::FieldRole)->widget()))->setText("");
		((QLabel*)(_detailLayout->itemAt(3, QFormLayout::FieldRole)->widget()))->setText("");
		return;
	}

	FileData* file = (FileData*)(_filter->mapToSource(selected.first().topLeft()).internalPointer());
	qDebug() << file;

	((QLabel*)(_detailLayout->itemAt(0, QFormLayout::FieldRole)->widget()))->setText(QVariant(file->id()).toString());
	((QLabel*)(_detailLayout->itemAt(1, QFormLayout::FieldRole)->widget()))->setText(file->name());
	((QLabel*)(_detailLayout->itemAt(2, QFormLayout::FieldRole)->widget()))->setText(QVariant(file->size()).toString());
	((QLabel*)(_detailLayout->itemAt(3, QFormLayout::FieldRole)->widget()))->setText(file->mimeType());
}
