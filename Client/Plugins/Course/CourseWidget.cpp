#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>

CourseWidget::CourseWidget(ILessonManager *lessonManager, ITreePlugin *treePlugin, IFileManager *fileManager): QSplitter::QSplitter()
{
    QWidget *leftPane;
    QVBoxLayout *layout;

    this->lessonManager = lessonManager;
    this->treePlugin = treePlugin;
    this->fileManager = fileManager;
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
    this->fileIndex = lessonIndex.data(Qt::UserRole).toUInt();
    if (this->fileIndex)
    {
        this->lessonFile = this->fileManager->getFile(this->fileIndex);
        lessonFile->open(QIODevice::ReadOnly);
        connect(this->lessonFile, SIGNAL(fileSynchronized()), this, SLOT(ready()));
    }
}

void CourseWidget::pageSelected(const QModelIndex &item, const QModelIndex &olditem)
{
    ILesson::IPage *page;
    ILesson::IPage *oldpage;

    page = item.data(Qt::UserRole).value<ILesson::IPage *>();
    oldpage = olditem.data(Qt::UserRole).value<ILesson::IPage *>();
    if (page)
    {
        this->lessonManager->hidePage(oldpage);
        this->lessonManager->displayPage(page, this->pageWidget);
    }
}

void CourseWidget::ready()
{
    disconnect(this->lessonFile, SIGNAL(fileSynchronized()), this, SLOT(ready()));
    this->lessonFile->close();
    this->lessonFile->open(QIODevice::ReadOnly);
    this->lessonView->setModel(this->lessonManager->getLesson(this->fileIndex));
    this->lessonView->expandAll();
    connect(this->lessonView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(pageSelected(QModelIndex, QModelIndex)));
}
