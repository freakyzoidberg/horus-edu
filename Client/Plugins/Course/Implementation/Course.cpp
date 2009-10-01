#include "Course.h"

#include <QVBoxLayout>

#include "../../../../Common/Defines.h"

#include "CourseWidget.h"
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
		this->widget = new CreateWhiteBoard(this->parent, this->pluginManager);
		break ;
	case LEVEL_STUDENT:
		this->widget = new JoinWhiteBoard(this->parent, this->pluginManager);
		this->layout->addWidget(this->widget);
		connect(this->widget, SIGNAL(whiteBoardJoined(WhiteBoardData *)), this, SLOT(joinWhiteBoard(WhiteBoardData *)));
		break ;
	default :
		this->widget = 0;
		this->widget = new CreateWhiteBoard(this->parent, this->pluginManager); // to delete
		this->layout->addWidget(this->widget);
		connect(this->widget, SIGNAL(whiteBoardCreated(WhiteBoardData *)), this, SLOT(joinWhiteBoard(WhiteBoardData *)));
	}
}

void	Course::userUpdate()
{
	if (this->user->status() == Data::UPTODATE)
		createWidget();
}

QWidget             *Course::getWidget()
{
	this->user = pluginManager->currentUser();
	this->parent = new QWidget();
	this->layout = new QVBoxLayout(this->parent);
	this->layout->setMargin(0);
	this->createWidget();
	return (this->parent);
}

void				Course::joinWhiteBoard(WhiteBoardData *whiteBoardData)
{
	delete this->widget;
	this->widget = new CourseWidget(this->parent, whiteBoardData, this->pluginManager);
	this->back = new QPushButton(tr("Back"));
	this->layout->addWidget(this->widget);
	this->layout->addWidget(this->back);
	this->widget->show();
	this->back->show();
	connect(this->back, SIGNAL(clicked()), this, SLOT(goBack()));
}

void				Course::goBack()
{
	delete this->back;
	delete this->widget;
	this->createWidget();
}