#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>
#include <QMenu>

CourseWidget::CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager) : QSplitter(parent)
{
    QWidget *leftPane;
    QVBoxLayout *layout;

    lessonPlugin = pluginManager->findPlugin<ILessonManager *>("LessonManager");
	treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	whiteboardPlugin = pluginManager->findPlugin<WhiteBoardDataPlugin*>();
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
	this->pageWidget = new WhiteBoard(wbd, controllers, (ILesson *)this->categoryModel->index(0, 0, QModelIndex()).internalPointer());
    this->addWidget(this->pageWidget);
}


void CourseWidget::buildCategoryTree()
{
    this->categoryModel = this->lessonPlugin->getLessonModel();
    this->categoryView = new QTreeView(this);
    this->categoryView->setModel(this->categoryModel);
    this->categoryView->setAnimated(true);
    this->categoryView->setAutoExpandDelay(500);
	this->categoryView->setRootIsDecorated(false);
    this->categoryView->setHeaderHidden(true);
    this->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->categoryView->setSelectionBehavior(QAbstractItemView::SelectItems);
	this->categoryView->setRootIndex(this->categoryModel->index(0, 0, this->categoryView->rootIndex()));
    this->categoryView->setDragEnabled(true);
	this->categoryView->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(this->categoryView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
	this->categoryView->expandAll();
}

void CourseWidget::contextMenu(const QPoint &point)
{
	QModelIndex idx = this->categoryView->currentIndex();
	if (idx.isValid())
	{
		QList<QAction *> actions;
		actions.insert(actions.end(), new QAction("pwet", NULL));
		QMenu::exec(actions, this->categoryView->mapToGlobal(point));
	}
}
