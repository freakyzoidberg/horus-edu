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
#include "LibraryFilter.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/FileData.h"
#include "../../../Common/TreeData.h"

#include <QListView>
#include <QTreeView>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

LibraryWidget::LibraryWidget(PluginManager* pluginManager)
{
	QGridLayout* layout = new QGridLayout(this);

	_filter = new LibraryFilter(pluginManager->findPlugin<FileDataPlugin*>()->listModel(), this);

	QTreeView* tree = new QTreeView(this);
	tree->setModel(pluginManager->findPlugin<TreeDataPlugin*>()->treeModel());
	tree->setHeaderHidden(true);
	tree->expandAll();
	tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tree->setAcceptDrops(true);
	tree->viewport()->setAcceptDrops(true);
	tree->setDropIndicatorShown(true);
	tree->setDragDropMode(QAbstractItemView::DropOnly);

	_treeSelection = tree->selectionModel();
	connect(_treeSelection, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), _filter, SLOT(treeSelectionChange(QItemSelection,QItemSelection)));
	tree->selectAll();

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

void LibraryWidget::fileSelectionChange(const QItemSelection& selected, const QItemSelection&)
{
	if ( ! selected.count())
	{
		static_cast<QLabel*>(_detailLayout->itemAt(0, QFormLayout::FieldRole)->widget())->setText("");
		static_cast<QLabel*>(_detailLayout->itemAt(1, QFormLayout::FieldRole)->widget())->setText("");
		static_cast<QLabel*>(_detailLayout->itemAt(2, QFormLayout::FieldRole)->widget())->setText("");
		static_cast<QLabel*>(_detailLayout->itemAt(3, QFormLayout::FieldRole)->widget())->setText("");
		return;
	}

	FileData* file = (FileData*)(_filter->mapToSource(selected.first().topLeft()).internalPointer());

	static_cast<QLabel*>(_detailLayout->itemAt(0, QFormLayout::FieldRole)->widget())->setText(QVariant(file->id()).toString());
	static_cast<QLabel*>(_detailLayout->itemAt(1, QFormLayout::FieldRole)->widget())->setText(file->name());
	static_cast<QLabel*>(_detailLayout->itemAt(2, QFormLayout::FieldRole)->widget())->setText(QVariant(file->size()).toString());
	static_cast<QLabel*>(_detailLayout->itemAt(3, QFormLayout::FieldRole)->widget())->setText(file->mimeType());
}
