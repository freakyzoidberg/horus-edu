#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>

#include "../LessonManager/ILessonManager.h"
#include "../TreeManagement/ITreePlugin.h"

CourseWidget::CourseWidget(Course *plugin): QSplitter::QSplitter()
{
    QAbstractItemModel *model;
    QTreeView *view;
    ITreePlugin *treePlugin;

    treePlugin = qobject_cast<ITreePlugin *>(plugin->client->getPlugin("TreeManagement"));
    model = treePlugin->getTreeModel();
    this->plugin = plugin;
    this->model = model;
    view = new QTreeView(this);
    view->setModel(this->model);
    view->setAnimated(true);
    view->setAutoExpandDelay(500);
    view->setRootIsDecorated(false);
    this->addWidget(view);
    lesson = new QTreeView(this);
    lesson->setAnimated(true);
    lesson->setAutoExpandDelay(500);
    lesson->setRootIsDecorated(false);
    this->addWidget(lesson);
    this->page = new QWidget;
    this->addWidget(page);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    connect(view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(lessonSelected(QModelIndex)));
    QModelIndex toto;
//    select(toto);
}

void CourseWidget::lessonSelected(const QModelIndex &item)
{
    this->file = this->plugin->fileManager->getFile(2);// need to use next line
//    this->file = this->plugin->fileManager->getFile(item.data(42).toUInt());
    this->item = item;
    file->open(QIODevice::ReadOnly);
    connect(file, SIGNAL(readyRead()), this, SLOT(ready()));
}

void CourseWidget::pageSelected(const QModelIndex &item)
{
    ILessonManager *lessonManager;

    lessonManager = qobject_cast<ILessonManager *>(this->plugin->client->getPlugin("LessonManager"));
    if (lessonManager)
    {
        lessonManager->hideCurrentPage();
        lessonManager->displayPage(item.data(Qt::UserRole).value<ILesson::IPage *>(), this->page);
    }
}

void CourseWidget::ready()
{
    ILessonManager *lessonManager;

    disconnect(file, SIGNAL(readyRead()), this, SLOT(ready()));
    this->file->close();
    lessonManager = qobject_cast<ILessonManager *>(this->plugin->client->getPlugin("LessonManager"));
    if (lessonManager)
    {
        this->lesson->setModel(lessonManager->getLesson(2));// need to use next line
//        this->lesson->setModel(lessonManager->getLesson(item.data(42).toUInt()));
        connect(lesson->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(pageSelected(QModelIndex)));
    }
}
