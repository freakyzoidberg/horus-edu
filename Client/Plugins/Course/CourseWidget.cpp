#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>

CourseWidget::CourseWidget(): QSplitter::QSplitter()
{
    QFileSystemModel *model;
    QTreeView *view;

    model = new QFileSystemModel(this);
    model->setRootPath("/");
    view = new QTreeView(this);
    view->setModel(model);
    this->addWidget(view);
    this->addWidget(new QWidget(this));
}
