#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include <QSplitter>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QTreeView>

#include "Course.h"

class CourseWidget : public QSplitter
{
    Q_OBJECT
public:
    CourseWidget(Course *plugin);

private:
    QAbstractItemModel  *model;
    QTreeView *lesson;
    Course *plugin;

private slots:
    void select(const QModelIndex &item);
};
#endif // COURSEWIDGET_H
