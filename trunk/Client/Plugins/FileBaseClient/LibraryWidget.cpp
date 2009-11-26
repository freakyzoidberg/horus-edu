/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "LibraryWidget.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/FileData.h"
#include "../../../Common/TreeData.h"

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
	tree->setModel(pluginManager->findPlugin<TreeDataPlugin*>()->treeModel());
//	tree->expandAll();
	tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
//	tree->selectAll();
	tree->setHeaderHidden(true);
	_treeSelection = tree->selectionModel();
	connect(_treeSelection, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(treeSelectionChange(QItemSelection,QItemSelection)));

	_filter = new QSortFilterProxyModel(this);
	_filter->setSourceModel(pluginManager->findPlugin<FileDataPlugin*>()->listModel());
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

	_detailLayout->addRow("Id:", new QLabel);
	_detailLayout->addRow("Name:", new QLabel);
	_detailLayout->addRow("Size:", new QLabel);
	_detailLayout->addRow("MimeType:", new QLabel);
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
