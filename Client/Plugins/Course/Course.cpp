#include <QDebug>
#include <QLabel>

#include "Course.h"
#include "CourseWidget.h"

#include "../LessonManager/ILessonManager.h"
#include "../TreeManagement/ITreePlugin.h"

Q_EXPORT_PLUGIN2(Course, Course)

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
    ILessonManager  *lessonManager;
    ITreePlugin     *treePlugin;
    QWidget         *error;

    lessonManager = qobject_cast<ILessonManager *>(this->client->getPlugin("LessonManager"));
    treePlugin = qobject_cast<ITreePlugin *>(this->client->getPlugin("TreeManagement"));
    if (lessonManager && treePlugin)
        return (new CourseWidget(lessonManager, treePlugin, this->fileManager));
    error = new QWidget();
    new QLabel("This Plugin depend of 'LessonManager' and 'TreeManagement' plugins.", error);
    return (error);
}
