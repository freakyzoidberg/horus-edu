#include "Course.h"

#include "../../../../Common/Defines.h"
#include "CreateWhiteBoard.h"
#include "JoinWhiteBoard.h"

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
    return (tr("Course"));
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
	// following segfault...
	//this->user = pluginManager->currentUser();
	//connect(this->user, SIGNAL(updated()), this, SLOT(userUpdate()));
	//if (this->user->status() == Data::UPTODATE)
	//	this->createWidget();
    Plugin::load();
}

void	Course::unload()
{
    Plugin::unload();
}

void	Course::createWidget()
{
	switch (this->user->level())
	{
	case LEVEL_TEACHER:
		this->widget = new CreateWhiteBoard();
		break ;
	case LEVEL_STUDENT:
		this->widget = new JoinWhiteBoard(this->pluginManager);
		break ;
	default :
		this->widget = 0;
		this->widget = new JoinWhiteBoard(this->pluginManager); // to delete
	}
	//this->widget = new CourseWidget(lessonPlugin, treePlugin, whiteboardPlugin, _controllers);
}

void	Course::userUpdate()
{
	if (this->user->status() == Data::UPTODATE)
		createWidget();
}

QWidget             *Course::getWidget()
{
	// remove the following lines when core stop to delete widgets
	this->user = pluginManager->currentUser();
	connect(this->user, SIGNAL(updated()), this, SLOT(userUpdate()));
	if (this->user->status() == Data::UPTODATE)
		this->createWidget();
	// to here
	return (this->widget);
}
