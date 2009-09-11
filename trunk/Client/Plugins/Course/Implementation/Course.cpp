#include "Course.h"
#include "CourseWidget.h"

const QString    Course::pluginName() const
{
    return "Course";
}

const QString    Course::pluginVersion() const
{
    return "0.2";
}

const QString	Course::getDisplayableName()
{
    return ("Course");
}

bool	Course::canLoad() const
{
    if (pluginManager->findPlugin("LessonManager") && pluginManager->findPlugin<TreeDataPlugin *>("Tree Data Base") && pluginManager->findPlugin<FileDataPlugin *>("File Data Base"))
        return (true);
    return (false);
}

void	Course::load()
{
    lessonPlugin = pluginManager->findPlugin<ILessonManager *>("LessonManager");
    treePlugin = pluginManager->findPlugin<TreeDataPlugin *>("Tree Data Base");
    filePlugin = pluginManager->findPlugin<FileDataPlugin *>("File Data Base");
    Plugin::load();
}

void	Course::unload()
{
    delete lessonPlugin;
    delete treePlugin;
    delete filePlugin;
    Plugin::unload();
}

QWidget             *Course::getWidget()
{
    return new CourseWidget(lessonPlugin, treePlugin, filePlugin);
}
