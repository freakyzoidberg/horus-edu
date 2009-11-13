#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QSizePolicy>
#include <QGridLayout>
#include <QMenu>

CourseWidget::CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager, UserData *user) : QWidget(parent), user(user)
{
    QWidget *leftPane;
    QGridLayout* layout;

    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    lessonPlugin = pluginManager->findPlugin<ILessonManager *>("LessonManager");
    treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
    whiteboardPlugin = pluginManager->findPlugin<WhiteBoardDataPlugin*>();
    filePlugin = pluginManager->findPlugin<FileDataPlugin*>();
    QList<IDocumentController *> controllersList = pluginManager->findPlugins<IDocumentController *>();
    QHash<QString, IDocumentController *> controllers;
    foreach (IDocumentController *controller, controllersList)
    controllers[controller->getSupportedType()] = controller;
    this->buildCategoryTree();
    this->pageWidget = new WhiteBoard(wbd, controllers, this->categoryModel);

    if (user->level() == LEVEL_TEACHER)
    {
        splitter.setHandleWidth(2);
        layout->addWidget(&splitter);
        splitter.show();
        leftPane = new QWidget(this);
        splitter.addWidget(leftPane);
        QGridLayout *lpLayout;
        lpLayout = new QGridLayout(leftPane);
        lpLayout->setMargin(0);
        lpLayout->setSpacing(0);
        lpLayout->addWidget(this->categoryView);
        splitter.addWidget(this->pageWidget);
        splitter.setStretchFactor(0, 0);
        splitter.setStretchFactor(1, 3);
    }
    else
    {
        layout->addWidget(pageWidget);
        layout->setMargin(2);
    }

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
    if (user->level() == LEVEL_TEACHER)
    {
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
        this->categoryView->expandAll();
    }
}

void CourseWidget::contextMenu(const QPoint &point)
{
    /*
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
    */
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
