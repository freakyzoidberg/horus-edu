#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QMenu>

CourseWidget::CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager) : QSplitter(parent)
{
    QWidget *leftPane;
    QVBoxLayout *layout;

    lessonPlugin = pluginManager->findPlugin<ILessonManager *>("LessonManager");
	treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	whiteboardPlugin = pluginManager->findPlugin<WhiteBoardDataPlugin*>();
	filePlugin = pluginManager->findPlugin<FileDataPlugin*>();
	QList<IDocumentController *> controllersList = pluginManager->findPlugins<IDocumentController *>();
	QHash<QString, IDocumentController *> controllers;
	foreach (IDocumentController *controller, controllersList)
		controllers[controller->getSupportedType()] = controller;
    this->buildCategoryTree();
    leftPane = new QWidget(this);
    this->addWidget(leftPane);
    layout = new QVBoxLayout(leftPane);
    layout->addWidget(this->categoryView);
	layout->setMargin(0);
    leftPane->setLayout(layout);
	//TODO, chage 0 by the selected witheboard
	this->pageWidget = new WhiteBoard(wbd, controllers, this->categoryModel);
    this->addWidget(this->pageWidget);
	this->setStretchFactor(0, 0);
	this->setStretchFactor(1, 3);
	if (lessonIcon == NULL)
		lessonIcon = new QIcon(":/LessonIcon.png");
	if (sectionIcon == NULL)
		sectionIcon = new QIcon(":/SectionIcon.png");
	if (documentIcon == NULL)
		documentIcon = new QIcon(":/DocumentIcon.png");
}


void CourseWidget::buildCategoryTree()
{
    this->categoryModel = this->lessonPlugin->getLessonModel();
    this->categoryView = new QTreeView(this);
    this->categoryView->setModel(this->categoryModel);
    this->categoryView->setAnimated(true);
    this->categoryView->setAutoExpandDelay(500);
	//this->categoryView->setRootIsDecorated(false);
    this->categoryView->setHeaderHidden(true);
    this->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->categoryView->setSelectionBehavior(QAbstractItemView::SelectItems);
	//this->categoryView->setRootIndex(this->categoryModel->index(0, 0, this->categoryView->rootIndex()));
    this->categoryView->setDragEnabled(true);
	this->categoryView->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(this->categoryView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
	QObject::connect(this->categoryView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
	//this->categoryView->expandAll();
}

void CourseWidget::contextMenu(const QPoint &point)
{
	if (currentIndex.isValid())
	{
		QList<QAction *> actions;
		QObject* obj = static_cast<QObject *>(currentIndex.internalPointer());
		ILesson* lesson = dynamic_cast<ILesson *>(obj);
		ILessonSection* section = dynamic_cast<ILessonSection *>(obj);
		if (lesson || section)
		{
			QAction *action = new QAction(*sectionIcon, tr("createSection"), NULL);
			QObject::connect(action, SIGNAL(triggered()), this, SLOT(addSection()));
			actions.push_back(action);
			action = new QAction(*documentIcon, tr("createDocument"), NULL);
			QObject::connect(action, SIGNAL(triggered()), this, SLOT(addDocument()));
			actions.push_back(action);
		}
		TreeData* treedata = dynamic_cast<TreeData*>(obj);
		if (treedata && treedata->type() == "SUBJECT")
		{
			QAction *action = new QAction(*lessonIcon, tr("createLesson"), NULL);
			QObject::connect(action, SIGNAL(triggered()), this, SLOT(addLesson()));
			actions.push_back(action);
		}
		QMenu::exec(actions, this->categoryView->mapToGlobal(point));
	}
}

void CourseWidget::selectionChanged(QModelIndex current, QModelIndex previous)
{
	currentIndex = current;
}

void CourseWidget::addDocument()
{

}

void CourseWidget::addSection()
{

}

void CourseWidget::addLesson()
{
	categoryModel->createLesson(currentIndex);
}

QIcon		*CourseWidget::lessonIcon = NULL;
QIcon		*CourseWidget::sectionIcon = NULL;
QIcon		*CourseWidget::documentIcon = NULL;
