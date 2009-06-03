#ifndef COURSE_H
#define COURSE_H

#include <QtGui/QMainWindow>
#include <QTreeWidget>
#include <QPushButton>
#include "MainFrame_global.h"
#include <QtPlugin>
#include "../../../IClientPlugin.h"
#include "../../../IDisplayablePlugin.h"

namespace Ui
{
    class CourseClass;
}

class COURSESHARED_EXPORT Course : public IClientPlugin, public IDisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IDisplayablePlugin)

public:
    Course();
    ~Course();
public slots:
    void explorer();
    void ViewLesson();
private:
    Ui::CourseClass *ui;
    QWidget *fenetre;
    QTreeWidget *tree;
};

#endif // Course_H
