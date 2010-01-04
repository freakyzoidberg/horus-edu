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
#include "LibraryEdit.h"
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
#include <QDragEnterEvent>
#include <QUrl>
#include <QStackedLayout>

LibraryList::LibraryList(PluginManager* pluginManager, QStackedLayout* parent)
{
	_selectedFile = 0;
	_pluginManager = pluginManager;
	_parent = parent;

	QGridLayout* layout = new QGridLayout(this);
	TreeDataPlugin* treeDataPlugin = _pluginManager->findPlugin<TreeDataPlugin*>();
	UserDataPlugin* userDataPlugin = _pluginManager->findPlugin<UserDataPlugin*>();
	FileDataPlugin* fileDataPlugin = _pluginManager->findPlugin<FileDataPlugin*>();

	_filter = new LibraryFilterProxyModel(fileDataPlugin, this);
	_filter->nodeListChanged(treeDataPlugin->allDatas());

	QListView* list = new QListView(this);
	list->setModel(_filter);
	list->setDragEnabled(true);
	list->setDragDropMode(QAbstractItemView::DragOnly);
	list->setSelectionMode(QAbstractItemView::ExtendedSelection);
	connect(list, SIGNAL(  clicked(QModelIndex)), this, SLOT(  fileClicked(QModelIndex)));
	connect(list, SIGNAL(activated(QModelIndex)), this, SLOT(fileActivated(QModelIndex)));

	QLineEdit* matchLine = new QLineEdit(this);
	connect(matchLine, SIGNAL(textChanged(QString)), _filter, SLOT(setFilterRegExp(QString)));

	_grades = new QComboBox(this);
	_subjects = new QComboBox(this);
	_owners = new QComboBox(this);
	refreshGrades(0);
	refreshUsers(0);
	connect(treeDataPlugin, SIGNAL(dataStatusChanged(Data*)), this, SLOT(refreshGrades(Data*)));
	connect(userDataPlugin, SIGNAL(dataStatusChanged(Data*)), this, SLOT(refreshUsers(Data*)));
	connect(_grades, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	connect(_subjects, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	connect(_owners, SIGNAL(currentIndexChanged(int)), this, SLOT(userBoxChanged(int)));


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
	leftLayout->setMargin(8);
	leftLayout->setSpacing(0);
	layout->addLayout(leftLayout					, 1, 0, 8, 1);

	leftLayout->addWidget(new QLabel(tr("KeyWords:"), this));
	leftLayout->addWidget(matchLine);
	leftLayout->addWidget(new QLabel(tr("Grade:"), this));
	leftLayout->addWidget(_grades);
	leftLayout->addWidget(new QLabel(tr("Subject:"), this));
	leftLayout->addWidget(_subjects);
	leftLayout->addWidget(new QLabel(tr("Owner:"), this));
	leftLayout->addWidget(_owners);

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
	formLayout->setMargin(8);
	layout->addLayout(formLayout					, 1, 2);
	
	formLayout->addRow(tr("Name:"), new QLabel(this));
	formLayout->addRow(tr("Size:"), new QLabel(this));
	formLayout->addRow(tr("Key Words:"), new QLabel(this));
//	formLayout->addRow(tr("Status:"), new QWidget(this));

	label = new QLabel(tr("Actions:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	label->setMinimumWidth(200);
	layout->addWidget(label							, 2, 2);

	QVBoxLayout* rightLayout = new QVBoxLayout;
//	rightLayout->setMargin(8);
	layout->addLayout(rightLayout						, 3, 2);

	QPushButton* button;

	button = new QPushButton(tr("Add"), this);
	connect(button, SIGNAL(clicked()), this, SLOT(createButton()));
	rightLayout->addWidget(button);

	button = new QPushButton(tr("Edit"), this);
	connect(button, SIGNAL(clicked()), this, SLOT(editButton()));
	rightLayout->addWidget(button);

	button = new QPushButton(tr("Remove"), this);
	connect(button, SIGNAL(clicked()), this, SLOT(removeButton()));
	rightLayout->addWidget(button);

	setAcceptDrops(true);
}

void LibraryList::refreshUsers(Data*)
{
	quint32 ownerId = _owners->itemData(_owners->currentIndex()).toUInt();
	_owners->clear();
	_owners->addItem(tr("All"), 0);
	foreach (Data* data,  _pluginManager->findPlugin<UserDataPlugin*>()->allDatas())
	{
		UserData* user = static_cast<UserData*>(data);
		if (user->level() <= LEVEL_TEACHER)
			_owners->addItem(user->icon(), user->name() + ' ' + user->surname(), user->id());
	}
	_owners->setCurrentIndex(_owners->findData(ownerId));
}

void LibraryList::refreshGrades(Data*)
{
	TreeDataPlugin* treeDataPlugin = _pluginManager->findPlugin<TreeDataPlugin*>();

	quint32 gradeId = _grades->itemData(_grades->currentIndex()).toUInt();
	_grades->clear();
	_grades->addItem(tr("All"), 0);
	foreach (TreeData* node, treeDataPlugin->grades())
		_grades->addItem(node->icon(), node->name(), node->id());
	_grades->setCurrentIndex(_grades->findData(gradeId));

	QString subject = _subjects->itemText(_subjects->currentIndex());
	_subjects->clear();
	_subjects->addItem(tr("All"));
	_subjects->addItems(treeDataPlugin->subjects());
	if (subject.isEmpty())
		subject = tr("All");
	_subjects->setCurrentIndex(_subjects->findText(subject));
}

void LibraryList::comboBoxChanged(int)
{
	TreeDataPlugin* treeDataPlugin = _pluginManager->findPlugin<TreeDataPlugin*>();

	TreeData* grade = treeDataPlugin->node(_grades->itemData(_grades->currentIndex()).toUInt());
	QString subject = _subjects->currentText();

	QList<Data*> list;
	foreach (Data* data, treeDataPlugin->allDatas())
	{
		TreeData* node = static_cast<TreeData*>(data);

		if (node->isDescendantOf(grade) &&
			(subject == tr("All") || node->isInSubject(subject)))
			list.append(node);
	}

	_filter->nodeListChanged(list);
}

void LibraryList::userBoxChanged(int index)
{
	quint32 userId = _owners->itemData(index).toUInt();

	if (userId)
		_filter->filterUser( _pluginManager->findPlugin<UserDataPlugin*>()->user( userId ) );
	else
		_filter->filterUser( 0 );
}

void LibraryList::fileClicked(QModelIndex index)
{
	_selectedFile = static_cast<FileData*>(_filter->mapToSource(index).internalPointer());

	QFormLayout* form = static_cast<QFormLayout*>(static_cast<QGridLayout*>(layout())->itemAtPosition(1, 2)->layout());
	static_cast<QLabel*>(form->itemAt(0, QFormLayout::FieldRole)->widget())->setText(_selectedFile->name());
	static_cast<QLabel*>(form->itemAt(1, QFormLayout::FieldRole)->widget())->setText(QVariant(_selectedFile->size()).toString());
}

void LibraryList::fileActivated(QModelIndex index)
{
	_selectedFile = static_cast<FileData*>(_filter->mapToSource(index).internalPointer());
	editButton();
}

void LibraryList::editFinished()
{
	delete _parent->takeAt(0);
	_parent->addWidget(this);
}

void LibraryList::createButton()
{
	LibraryEdit* edit = new LibraryEdit(_pluginManager);
	connect(edit, SIGNAL(exited()), this, SLOT(editFinished()));
	_parent->takeAt(0);
	_parent->addWidget(edit);
}

void LibraryList::editButton()
{
	if ( ! _selectedFile)
		return;

	LibraryEdit* edit = new LibraryEdit(_pluginManager, _selectedFile);
	connect(edit, SIGNAL(exited()), this, SLOT(editFinished()));
	_parent->takeAt(0);
	_parent->addWidget(edit);
}

void LibraryList::removeButton()
{
	if ( ! _selectedFile)
		return;
	_selectedFile->remove();
	_selectedFile = 0;
	QFormLayout* form = static_cast<QFormLayout*>(static_cast<QGridLayout*>(layout())->itemAtPosition(1, 2)->layout());
	static_cast<QLabel*>(form->itemAt(0, QFormLayout::FieldRole)->widget())->setText("");
	static_cast<QLabel*>(form->itemAt(1, QFormLayout::FieldRole)->widget())->setText("");
}

void LibraryList::dragEnterEvent(QDragEnterEvent *event)
{
	if ( ! event->mimeData()->hasUrls()	|| event->mimeData()->hasFormat(("x-horus/x-data")))
		return;
	if (event->mimeData()->urls().count() > 1)
		return;
	if ( ! QFile(event->mimeData()->urls().first().toLocalFile()).exists())
		return;

	event->acceptProposedAction();
}

void LibraryList::dropEvent(QDropEvent* event)
{
	if ( ! event->mimeData()->hasUrls()	|| event->mimeData()->hasFormat(("x-horus/x-data")))
		return;
	if (event->mimeData()->urls().count() > 1)
		return;
	if ( ! QFile(event->mimeData()->urls().first().toLocalFile()).exists())
		return;

	TreeDataPlugin* treeDataPlugin = _pluginManager->findPlugin<TreeDataPlugin*>();
	TreeData* node = treeDataPlugin->node(_grades->itemData(_grades->currentIndex()).toUInt());
	QString subject = _subjects->currentText();

	if (node != treeDataPlugin->rootNode() && subject != tr("All"))
	{
		foreach (Data* data, treeDataPlugin->allDatas())
		{
			TreeData* n = static_cast<TreeData*>(data);
			if (n->isDescendantOf(node) && n->type() == "SUBJECT" && n->name() == subject)
			{
				node = n;
				break;
			}
		}
	}

	LibraryEdit* edit = new LibraryEdit(_pluginManager, event->mimeData()->urls().first().path());
	connect(edit, SIGNAL(exited()), this, SLOT(editFinished()));
	_parent->takeAt(0);
	_parent->addWidget(edit);

	event->acceptProposedAction();
}
