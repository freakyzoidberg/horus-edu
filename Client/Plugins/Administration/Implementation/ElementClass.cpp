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
#include		"ElementClass.h"

#include		<QBoxLayout>

#include		"../../../../Common/TreeData.h"

ElementClass::ElementClass(QWidget *parent, TreeDataPlugin *treeDataPlugin) : StructureElement(parent, treeDataPlugin)
{
	QBoxLayout	*mainLayout;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	classesFilter = new QSortFilterProxyModel(this);
	classesFilter->setSourceModel(treeDataPlugin->listModel());
	classesFilter->setFilterRole(Data::FILTER_ROLE);
	classesFilter->setFilterKeyColumn(0);
	classesFilter->setDynamicSortFilter(true);
	classesFilter->setFilterFixedString("GRADE");
	classListView = new QListView(this);
	classListView->setSelectionMode(QAbstractItemView::SingleSelection);
	classListView->setViewMode(QListView::IconMode);
	classListView->setMovement(QListView::Static);
	classListView->setFlow(QListView::TopToBottom);
	classListView->setGridSize(QSize(64, 54));
	classListView->setWrapping(true);
	classListView->setMaximumHeight(64);
	classListView->setSelectionRectVisible(false);
	classListView->setDragEnabled(false);
	classListView->setAcceptDrops(false);
	classListView->viewport()->setAcceptDrops(false);
	classListView->setDropIndicatorShown(false);
	classListView->setModel(classesFilter);
	mainLayout->addWidget(classListView);
	connect(classListView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(classSelected(const QItemSelection &, const QItemSelection &)));
	connect(treeDataPlugin, SIGNAL(dataCreated(Data *)), classListView, SLOT(update()));
	connect(treeDataPlugin, SIGNAL(dataUpdated(Data *)), classListView, SLOT(update()));
	connect(treeDataPlugin, SIGNAL(dataRemoved(Data *)), classListView, SLOT(update()));
}

void			ElementClass::update()
{
	classListView->update();
}

void			ElementClass::addElement()
{
	_form->setTitle(tr("Class informations"));
	_form->setTeacherVisibility(false);
	_form->setName("");
	_form->setTeacher(0);
	editing = 0;
}

void			ElementClass::editElement()
{
	if (classListView->selectionModel()->hasSelection())
	{
		_form->setTitle(tr("Class informations"));
		_form->setTeacherVisibility(false);
		editing = static_cast<TreeData *>(classesFilter->mapToSource(classListView->selectionModel()->currentIndex()).internalPointer());
		_form->setName(editing->name());
		_form->setTeacher(editing->user());
	}
	else
		addElement();
}

void			ElementClass::removeElement()
{
	if (classListView->selectionModel()->hasSelection())
		static_cast<TreeData *>(classesFilter->mapToSource(classListView->selectionModel()->currentIndex()).internalPointer())->remove();
}

void			ElementClass::validateElement()
{
	if (editing)
	{
		editing->setName(_form->getName());
		editing->setUser(_form->getTeacher());
		editing->save();
	}
	else
	{
		editing = _treeDataPlugin->createNode();
		editing->setName(_form->getName());
		editing->setUser(_form->getTeacher());
		editing->setType("GRADE");
		editing->setParent(_treeDataPlugin->rootNode());
		editing->create();
	}
}

void			ElementClass::classSelected(const QItemSelection &selected, const QItemSelection &)
{
	if (selected.indexes().size() == 1)
		emit enabled();
	else
		emit disabled();
}
