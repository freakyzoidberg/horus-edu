#include <QDebug>
#include <QLabel>

#include "Course.h"
#include "CourseWidget.h"

#include "../../../Common/PluginManager.h"

//#include "../LessonManager/ILessonManager.h"
//#include "../TreeManagement/ITreePlugin.h"
#include "../../ClientEvents.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;

const QString    Course::getName() const
{
    return "Course";
}

const QString    Course::getVersion() const
{
    return "0.1";
}

bool                Course::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoadPluginEvent)
        return (true);
    qDebug() << "Course: Received Event not managed" << event;
    return (false);
}

QWidget             *Course::getWidget()
{
    ILessonManager  *lessonManager;
    ITreePlugin     *treePlugin;
    QWidget         *error;

//    lessonManager = PluginManager().findPlugin<ILessonManager*>("LessonManager");
//    treePlugin = PluginManager().findPlugin<ITreePlugin*>("TreeManagement");
//    if (lessonManager && treePlugin)
//        return new CourseWidget(lessonManager, treePlugin, PluginManager().findPlugin<IFilePlugin*>("FileManagement"));
    error = new QWidget();
    new QLabel("This Plugin depend of 'LessonManager' and 'TreeManagement' plugins.", error);
    return error;
}
