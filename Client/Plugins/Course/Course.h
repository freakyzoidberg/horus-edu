#ifndef COURSE_H
#define COURSE_H

#include <QtGui/QMainWindow>
#include <QTreeWidget>
#include <QtPlugin>
#include "../../../Common/Plugin.h"
#include "../../DisplayablePlugin.h"
#include "../../../Common/NetworkPlugin.h"
//#include "../FileManagement/IFilePlugin.h"

//class Ui::CourseClass;

class Course : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    const QString       getName() const;
    const QString       getVersion() const;
    bool                event(QEvent *event);
    QWidget*            getWidget();

private:
    //Ui::CourseClass*    ui;
    QWidget*            fenetre;
    QTreeWidget*        tree;
};

#endif // Course_H
