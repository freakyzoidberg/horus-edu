#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>

CourseWidget::CourseWidget(ILessonManager *lessonManager, ITreePlugin *treePlugin, IFilePlugin *fileManagement): QSplitter::QSplitter()
{
    QWidget *leftPane;
    QVBoxLayout *layout;

    this->lessonManager = lessonManager;
    this->treePlugin = treePlugin;
    this->fileManagement = fileManagement;
    this->buildCategoryTree();
    this->buildLessonTree();
    leftPane = new QWidget(this);
    this->addWidget(leftPane);
    layout = new QVBoxLayout(leftPane);
    layout->addWidget(this->categoryView);
    layout->addWidget(this->lessonView);
    leftPane->setLayout(layout);
    this->pageWidget = new QWidget;
    this->addWidget(this->pageWidget);
    oldpage = 0;
}

void CourseWidget::buildCategoryTree()
{
    this->categoryModel = this->treePlugin->getTreeModel();
    this->categoryView = new QTreeView(this);
    this->categoryView->setModel(this->categoryModel);
    this->categoryView->setAnimated(true);
    this->categoryView->setAutoExpandDelay(500);
    this->categoryView->setRootIsDecorated(false);
    this->categoryView->setHeaderHidden(true);
    this->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->categoryView->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->categoryView->expandAll();
    this->categoryView->indexAbove(this->categoryView->rootIndex());
    connect(this->categoryView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(lessonSelected(QModelIndex)));
}

void CourseWidget::buildLessonTree()
{
    this->lessonView = new QTreeView(this);
    this->lessonView->setAnimated(true);
    this->lessonView->setAutoExpandDelay(500);
    this->lessonView->setRootIsDecorated(false);
    this->lessonView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->lessonView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void CourseWidget::lessonSelected(const QModelIndex &lessonIndex)
{
        if (oldpage)
        this->lessonManager->hidePage(oldpage);
    this->fileIndex = lessonIndex.data(Qt::UserRole).toUInt();
    if (this->fileIndex)
    {
        this->lessonFile = this->fileManagement->getFile(this->fileIndex);
        lessonFile->open(QIODevice::ReadOnly);
        connect(this->lessonFile, SIGNAL(fileSynchronized()), this, SLOT(ready()));
    }
}

void CourseWidget::pageSelected(const QModelIndex &item)
{
    ILesson::IPage *page;
    page = item.data(Qt::UserRole).value<ILesson::IPage *>();
        if (oldpage)
        this->lessonManager->hidePage(oldpage);
    if (page)
    {
        this->lessonManager->displayPage(page, this->pageWidget);
    }
    oldpage = item.data(Qt::UserRole).value<ILesson::IPage *>();
}

void CourseWidget::ready()
{
    disconnect(this->lessonFile, SIGNAL(fileSynchronized()), this, SLOT(ready()));
    this->lessonFile->close();
    this->lessonFile->open(QIODevice::ReadOnly);
    this->lessonView->setModel(this->lessonManager->getLesson(this->fileIndex));
    this->lessonView->expandAll();
    connect(this->lessonView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(pageSelected(QModelIndex)));
}