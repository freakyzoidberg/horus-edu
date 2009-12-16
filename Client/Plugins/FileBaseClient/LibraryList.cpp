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
#include "LibraryList.h"
#include "LibraryFilterProxyModel.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/UserData.h"
#include "../../../Common/FileData.h"
#include <QListView>
#include <QLabel>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QFormLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QComboBox>

LibraryList::LibraryList(PluginManager* pluginManager)
{
	QGridLayout* layout = new QGridLayout(this);

	_treeDataPlugin = pluginManager->findPlugin<TreeDataPlugin*>();
	_userDataPlugin = pluginManager->findPlugin<UserDataPlugin*>();

	_filter = new LibraryFilterProxyModel(pluginManager->findPlugin<FileDataPlugin*>()->listModel(), this);
	_filter->filterUser(0);
	_filter->nodeListChanged(_treeDataPlugin->allDatas());

	QListView* list = new QListView(this);
	list->setModel(_filter);
	list->setDragEnabled(true);
	list->setDragDropMode(QAbstractItemView::DragOnly);
	list->setSelectionMode(QAbstractItemView::ExtendedSelection);
	connect(list, SIGNAL(  clicked(QModelIndex)), this, SLOT(  fileClicked(QModelIndex)));
	connect(list, SIGNAL(activated(QModelIndex)), this, SLOT(fileActivated(QModelIndex)));

	QLineEdit* matchLine = new QLineEdit(this);
	connect(matchLine, SIGNAL(textChanged(QString)), _filter, SLOT(setFilterRegExp(QString)));

	grades = new QComboBox(this);
	grades->addItem(tr("All"), 0);
	foreach (TreeData* node, _treeDataPlugin->grades())
		grades->addItem(node->icon(), node->name(), node->id());
	connect(grades, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));

	subjects = new QComboBox(this);
	subjects->addItem(tr("All"));
	subjects->addItems(_treeDataPlugin->subjects());
	connect(subjects, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));

	owners = new QComboBox(this);
	owners->addItem(tr("All"), 0);
	foreach (Data* data, _userDataPlugin->allDatas())
	{
		UserData* user = static_cast<UserData*>(data);
		if (user->level() <= LEVEL_TEACHER)
			owners->addItem(user->icon(), user->name() + ' ' + user->surname(), user->id());
	}
	connect(owners, SIGNAL(currentIndexChanged(int)), this, SLOT(userBoxChanged(int)));


	layout->setRowStretch(9, 1);
	layout->setColumnStretch(1, 1);
	layout->setSpacing(0);
	layout->setMargin(0);

	QLabel* label;

	label = new QLabel(tr("Filter by:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	label->setMinimumWidth(130);
	layout->addWidget(label							, 0, 0);


	QVBoxLayout* leftLayout = new QVBoxLayout;
	layout->addLayout(leftLayout					, 1, 0, 8, 1);

	leftLayout->addWidget(new QLabel(tr("KeyWords:"), this));
	leftLayout->addWidget(matchLine);
	leftLayout->addWidget(new QLabel(tr("Grade:"), this));
	leftLayout->addWidget(grades);
	leftLayout->addWidget(new QLabel(tr("Subject:"), this));
	leftLayout->addWidget(subjects);
	leftLayout->addWidget(new QLabel(tr("Owner:"), this));
	leftLayout->addWidget(owners);

	label = new QLabel(tr("Select a file:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	layout->addWidget(label							, 0, 1);
	layout->addWidget(list							, 1, 1, 9, 1);

	label = new QLabel(tr("Informations:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	label->setMinimumWidth(200);
	layout->addWidget(label							, 0, 2);

	QFormLayout* formLayout = new QFormLayout;
	layout->addLayout(formLayout					, 1, 2);

	formLayout->addRow(tr("Name:"), new QLabel(this));
	formLayout->addRow(tr("Size:"), new QLabel(this));
	formLayout->addRow(tr("Mime Type:"), new QLabel(this));
	formLayout->addRow(tr("Key Words:"), new QLabel(this));

	label = new QLabel(tr("Actions:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	label->setMinimumWidth(200);
	layout->addWidget(label							, 2, 2);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	layout->addLayout(rightLayout						, 3, 2);
	rightLayout->addWidget(new QPushButton(tr("Add a file"), this));
	rightLayout->addWidget(new QPushButton(tr("Edit a file"), this));
	rightLayout->addWidget(new QPushButton(tr("Remove a file"), this));
}

LibraryList::~LibraryList()
{
//	QLayoutItem* item;
//	while ((item = laytakeAt(0)))
//	{
//		delete item->widget();
//		delete item;
//	}
}

void LibraryList::comboBoxChanged(int)
{
	QList<Data*> list;
	foreach (Data* data, _treeDataPlugin->allDatas())
	{
		TreeData* node = static_cast<TreeData*>(data);
		TreeData* grade = _treeDataPlugin->node(grades->itemData(grades->currentIndex()).toUInt());
		QString subject = subjects->currentText();

		if (node->isDescendantOf(grade) &&
			(subject == tr("All") || node->isInSubject(subject)))
			list.append(node);
	}

	_filter->nodeListChanged(list);
}

void LibraryList::userBoxChanged(int index)
{
	quint32 userId = owners->itemData(index).toUInt();

	if (userId)
		_filter->filterUser( _userDataPlugin->user( userId ) );
	else
		_filter->filterUser( 0 );
}

void LibraryList::fileClicked(QModelIndex index)
{
	_selectedFile = static_cast<FileData*>(_filter->mapToSource(index).internalPointer());

	QFormLayout* form = static_cast<QFormLayout*>(static_cast<QGridLayout*>(layout())->itemAtPosition(1, 2)->layout());
	static_cast<QLabel*>(form->itemAt(0, QFormLayout::FieldRole)->widget())->setText(_selectedFile->name());
	static_cast<QLabel*>(form->itemAt(1, QFormLayout::FieldRole)->widget())->setText(QVariant(_selectedFile->size()).toString());
	static_cast<QLabel*>(form->itemAt(2, QFormLayout::FieldRole)->widget())->setText(_selectedFile->mimeType());
	static_cast<QLabel*>(form->itemAt(3, QFormLayout::FieldRole)->widget())->setText("");
}

void LibraryList::fileActivated(QModelIndex index)
{
	_selectedFile = static_cast<FileData*>(_filter->mapToSource(index).internalPointer());
	emit editFile(_selectedFile);
}

void LibraryList::createButton()
{

}

void LibraryList::editButton()
{
	emit editFile(_selectedFile);
}

void LibraryList::removeButton()
{

}
