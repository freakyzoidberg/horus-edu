#include <QtCore/qplugin.h>
#include <QDebug>
#include "Course.h"
#include "CourseWidget.h"

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
    return (new CourseWidget(this));
}


void                Course::recvPacket(const PluginPacket &packet)
{
    //do something
}
