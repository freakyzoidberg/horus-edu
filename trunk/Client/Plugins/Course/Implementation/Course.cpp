#include "Course.h"

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/FileDataPlugin.h"
#include "../../LessonManager/ILessonManager.h"

#include "CourseWidget.h"

const QString    Course::pluginName() const
{
    return "Course";
}

const QString    Course::pluginVersion() const
{
    return "0.2";
}

bool	Course::canLoad() const
{
	if (pluginManager->findPlugin("LessonManager") && pluginManager->findPlugin<TreeDataPlugin *>("TreeDataPlugin") && pluginManager->findPlugin<FileDataPlugin *>("FileDataPlugin"))
		return (true);
	return (false);
}

void	Course::load()
{
    ILessonManager  *lessonPlugin;
    TreeDataPlugin  *treePlugin;
	FileDataPlugin	*filePlugin;

    lessonPlugin = this->pluginManager->findPlugin<ILessonManager *>("LessonManager");
    treePlugin = this->pluginManager->findPlugin<TreeDataPlugin *>("TreeDataPlugin");
	filePlugin = this->pluginManager->findPlugin<FileDataPlugin *>("FileDataPlugin");
	this->widget = new CourseWidget(lessonPlugin, treePlugin, filePlugin);
	Plugin::load();
}

void	Course::unload()
{
	delete this->widget;
	Plugin::unload();
}

QWidget             *Course::getWidget()
{
	return (this->widget);
}
