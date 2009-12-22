#include		"ElementSubject.h"

#include		<QBoxLayout>

#include		"../../../../Common/TreeData.h"

ElementSubject::ElementSubject(QWidget *parent, TreeDataPlugin *treeDataPlugin) : StructureElement(parent, treeDataPlugin)
{
	QBoxLayout	*mainLayout;

	_class = 0;
	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	classFilter = new QSortFilterProxyModel(this);
	classFilter->setSourceModel(treeDataPlugin->listModel());
	classFilter->setFilterRole(Data::FILTER_ROLE);
	classFilter->setFilterKeyColumn(1);
	classFilter->setDynamicSortFilter(true);
	subjectFilter = new QSortFilterProxyModel(this);
	subjectFilter->setSourceModel(classFilter);
	subjectFilter->setFilterRole(Data::FILTER_ROLE);
	subjectFilter->setFilterKeyColumn(0);
	subjectFilter->setDynamicSortFilter(true);
	subjectFilter->setFilterFixedString("SUBJECT");
	subjectListView = new QListView(this);
	subjectListView->setSelectionMode(QAbstractItemView::SingleSelection);
	subjectListView->setViewMode(QListView::IconMode);
	subjectListView->setMovement(QListView::Static);
	subjectListView->setFlow(QListView::TopToBottom);
	subjectListView->setGridSize(QSize(64, 54));
	subjectListView->setWrapping(true);
	subjectListView->setMaximumHeight(64);
	subjectListView->setSelectionRectVisible(false);
	subjectListView->setDragEnabled(false);
	subjectListView->setAcceptDrops(false);
	subjectListView->viewport()->setAcceptDrops(false);
	subjectListView->setDropIndicatorShown(false);
	subjectListView->setModel(subjectFilter);
	mainLayout->addWidget(subjectListView);
	connect(subjectListView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(subjectSelected(const QItemSelection &, const QItemSelection &)));
	connect(treeDataPlugin, SIGNAL(dataCreated(Data *)), subjectListView, SLOT(update()));
	connect(treeDataPlugin, SIGNAL(dataUpdated(Data *)), subjectListView, SLOT(update()));
	connect(treeDataPlugin, SIGNAL(dataRemoved(Data *)), subjectListView, SLOT(update()));
}

void			ElementSubject::update()
{
	subjectListView->update();
}

void			ElementSubject::setClass(TreeData *node)
{
	_class = node;
	classFilter->setFilterRegExp(QRegExp("\\b" + QString::number(node->id()) + "\\b"));
}

void			ElementSubject::addElement()
{
	_form->setTitle(tr("Subject informations"));
	_form->setTeacherVisibility(false);
	_form->setName("");
	_form->setTeacher(0);
	editing = 0;
}

void			ElementSubject::editElement()
{
	if (subjectListView->selectionModel()->hasSelection())
	{
		_form->setTitle(tr("Subject informations"));
		_form->setTeacherVisibility(false);
		editing = static_cast<TreeData *>(classFilter->mapToSource(subjectFilter->mapToSource(subjectListView->selectionModel()->currentIndex())).internalPointer());
		_form->setName(editing->name());
		_form->setTeacher(editing->user());
	}
	else
		addElement();
}

void			ElementSubject::removeElement()
{
	if (subjectListView->selectionModel()->hasSelection())
		static_cast<TreeData *>(classFilter->mapToSource(subjectFilter->mapToSource(subjectListView->selectionModel()->currentIndex())).internalPointer())->remove();
}

void			ElementSubject::validateElement()
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
		if (_class)
			editing->setParent(_class);
		editing->setName(_form->getName());
		editing->setUser(_form->getTeacher());
		editing->setType("SUBJECT");
		editing->setParent(_treeDataPlugin->rootNode());
		editing->create();
	}
}

void			ElementSubject::subjectSelected(const QItemSelection &selected, const QItemSelection &)
{
	if (selected.indexes().size() == 1)
		emit enabled();
	else
		emit disabled();
}
