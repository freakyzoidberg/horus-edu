#include <QtCore/qplugin.h>
#include <QDebug>
#include "Course.h"
#include "CourseWidget.h"

Q_EXPORT_PLUGIN2(Course, Course)

Course::Course()
{


}

Course::~Course()
{

}

const QByteArray    Course::getName() const
{
    return ("Course");
}

const QByteArray    Course::getVersion() const
{
    return ("0.1");
}

QStringList         Course::getPluginsRequired() const
{
    return (QStringList());
}

QStringList         Course::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList         Course::getPluginsRecommended() const
{
    return (QStringList());
}

bool                Course::event(QEvent *event)
{
    qDebug() << "Course: Received Event not managed" << event;
    return (false);
}

QWidget             *Course::getWidget()
{
    return (new CourseWidget());
}

void Course::explorer()
{

    //build tree
this->tree = new QTreeWidget(this->fenetre);
this->tree->resize(150,200);

tree->setMaximumWidth(200);
tree->setColumnCount(1);
tree->setHeaderLabel("matiere");

//build index
QTreeWidgetItem *cours1 = new QTreeWidgetItem(tree);
cours1->setText(0,"cours 1");

//build child
QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
lesson1->setText(0,"lesson 1");

QTreeWidgetItem *cours2 = new QTreeWidgetItem;
cours2->setText(0,"cours 2");

tree->insertTopLevelItem(0, cours1);
tree->insertTopLevelItem(1, cours2);
tree->show();
}

void    Course::ViewLesson()
{
   QTreeWidget *tree = new QTreeWidget;
tree->setColumnCount(1);
tree->setHeaderLabel("test");
tree->show();
}
