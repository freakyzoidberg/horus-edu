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
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    connect(view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(select(QModelIndex)));
}

void CourseWidget::select(const QModelIndex &item)
{
    this->file = this->plugin->fileManager->getFile(2);// need to use next line
//    this->file = this->plugin->fileManager->getFile(item.data(42).toUInt());
    this->item = item;
//    file->open(QIODevice::ReadOnly);
//    connect(file, SIGNAL(readyRead()), this, SLOT(ready()));
}

void CourseWidget::ready()
{
    ILessonManager *lessonManager;

    disconnect(file, SIGNAL(readyRead()), this, SLOT(ready()));
    this->file->close();
    qDebug() << item.data(42);
    qDebug() << item;
    lessonManager = qobject_cast<ILessonManager *>(this->plugin->client->getPlugin("LessonManager"));
    if (lessonManager)
    {
//        this->lesson->setModel(lessonManager->getLesson(2));// need to use next line
//        this->lesson->setModel(lessonManager->getLesson(item.data(42).toUInt()));
    }
}
