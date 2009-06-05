#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include <QSplitter>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QTreeView>

#include "Course.h"
#include "../../IFile.h"

class CourseWidget : public QSplitter
{
    Q_OBJECT
public:
    CourseWidget(Course *plugin);

private:
    QAbstractItemModel  *model;
    QTreeView *lesson;
    QWidget *page;
    Course *plugin;
    IFile *file;
    QModelIndex item;

private slots:
    void lessonSelected(const QModelIndex &item);
    void pageSelected(const QModelIndex &item);
    void ready();
};
#endif // COURSEWIDGET_H
