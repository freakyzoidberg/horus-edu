#include "Course.h"

#include <QVBoxLayout>

#include "../../../../Common/Defines.h"

#include "CourseWidget.h"

#include "ClassTab.h"
#include "LessonTabTeacher.h"
#include "LessonTabStudent.h"

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

QWidget             *Course::getWidget()
{
	this->user = pluginManager->currentUser();
	switch (this->user->level())
	{
	case LEVEL_STUDENT:
	case LEVEL_TEACHER:
		break;
	default:
		return NULL;
	}
	QTabWidget *tabwidget = new QTabWidget;
	this->widget = tabwidget;
	switch (this->user->level())
	{
	case LEVEL_STUDENT:
                tabwidget->addTab(new LessonTabStudent(this->pluginManager), QIcon(":/Ui/book.png"), tr("Lessons"));
                tabwidget->addTab(new ClassTab(this->pluginManager, this->user), QIcon(":/Ui/desk.png"), tr("Classes"));
		break;
	case LEVEL_TEACHER:
		tabwidget->addTab(new LessonTabTeacher(this->pluginManager), QIcon(":/Ui/book.png"), tr("Lessons"));
                tabwidget->addTab(new ClassTab(this->pluginManager, this->user), QIcon(":/Ui/desk.png"), tr("Classes"));
		break;
	default:
		return NULL;
	}
	return (tabwidget);
}

void				Course::joinWhiteBoard(WhiteBoardData *whiteBoardData)
{
	delete this->widget;
        this->widget = new CourseWidget(this->parent, whiteBoardData, this->pluginManager, user);
	this->back = new QPushButton(tr("Back"));
	this->layout->addWidget(this->widget);
	this->layout->addWidget(this->back);
	this->widget->show();
	this->back->show();
	connect(this->back, SIGNAL(clicked()), this, SLOT(goBack()));
}

