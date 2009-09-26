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

const QString	Course::getDisplayableName() const
{
    return ("Course");
}

int		Course::getOrder() const
{
	return (1);
}

QIcon			Course::getIcon() const
{
	return (QIcon(":/icon"));
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
	treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	whiteboardPlugin = pluginManager->findPlugin<WhiteBoardDataPlugin*>();
	QList<IDocumentController *> controllersList = pluginManager->findPlugins<IDocumentController *>();
	foreach (IDocumentController *controller, controllersList)
		this->_controllers[controller->getSupportedType()] = controller;
    Plugin::load();
}

void	Course::unload()
{
    Plugin::unload();
}

QWidget             *Course::getWidget()
{
	return new CourseWidget(lessonPlugin, treePlugin, whiteboardPlugin, _controllers);
}
