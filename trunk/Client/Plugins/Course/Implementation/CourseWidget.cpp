#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>

CourseWidget::CourseWidget(ILessonManager *_lessonPlugin, TreeDataPlugin *_treePlugin, FileDataPlugin *_filePlugin, QHash<QString, IDocumentController *> controllers) : QSplitter()
{
    QWidget *leftPane;
    QVBoxLayout *layout;

    this->lessonPlugin = _lessonPlugin;
    this->treePlugin = _treePlugin;
    this->filePlugin = _filePlugin;
    this->buildCategoryTree();
    leftPane = new QWidget(this);
    this->addWidget(leftPane);
    layout = new QVBoxLayout(leftPane);
    layout->addWidget(this->categoryView);
    leftPane->setLayout(layout);
    this->pageWidget = new WhiteBoard(controllers);
    this->addWidget(this->pageWidget);

    Items *test = new Items(this->pageWidget);
    Items *test2 = new Items(this->pageWidget);

    test2->move(0,0);
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
	this->categoryView->setDragEnabled(true);
    this->categoryView->expandAll();
    //this->categoryView->indexAbove(this->categoryView->rootIndex()); // useless
    connect(this->categoryView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(lessonSelected(QModelIndex)));
}

void CourseWidget::lessonSelected(const QModelIndex &lessonIndex)
{

}
