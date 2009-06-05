#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>

CourseWidget::CourseWidget(ILessonManager *lessonManager, ITreePlugin *treePlugin, IFileManager *fileManager): QSplitter::QSplitter()
{
    this->lessonManager = lessonManager;
    this->treePlugin = treePlugin;
    this->fileManager = fileManager;
    this->buildCategoryTree();
    this->buildLessonTree();
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
    this->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->categoryView->setSelectionBehavior(QAbstractItemView::SelectItems);
    connect(this->categoryView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(lessonSelected(QModelIndex)));
    this->addWidget(this->categoryView);
}

void CourseWidget::buildLessonTree()
{
    this->lessonView = new QTreeView(this);
    this->lessonView->setAnimated(true);
    this->lessonView->setAutoExpandDelay(500);
    this->lessonView->setRootIsDecorated(false);
    this->lessonView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->lessonView->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->addWidget(this->lessonView);
}

void CourseWidget::lessonSelected(const QModelIndex &lessonIndex)
{
    this->fileIndex = lessonIndex.data(Qt::UserRole).toUInt();
    this->fileIndex = 2; // ----------------- NEED TO BE DELETED
    if (this->fileIndex)
    {
        this->lessonFile = this->fileManager->getFile(this->fileIndex);
        lessonFile->open(QIODevice::ReadOnly);
        connect(this->lessonFile, SIGNAL(readyRead()), this, SLOT(ready()));
    }
}

void CourseWidget::pageSelected(const QModelIndex &item)
{
    ILesson::IPage *page;

    page = item.data(Qt::UserRole).value<ILesson::IPage *>();
    if (page)
    {
        this->lessonManager->hidePage(page);
        this->lessonManager->displayPage(page, this->pageWidget);
    }
}

void CourseWidget::ready()
{
    disconnect(this->lessonFile, SIGNAL(readyRead()), this, SLOT(ready()));
    this->lessonFile->close();
    this->lessonView->setModel(this->lessonManager->getLesson(this->fileIndex));
    connect(this->lessonView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(pageSelected(QModelIndex)));
}
