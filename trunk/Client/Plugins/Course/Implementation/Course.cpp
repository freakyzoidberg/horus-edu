/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
            //tabwidget->addTab(new LessonTabStudent(this->pluginManager), QIcon(":/Ui/book.png"), tr("Lessons"));
            tabwidget->addTab(new ClassTab(this->pluginManager, this->user), QIcon(":/Ui/desk.png"), tr("Classes"));
		break;
	case LEVEL_TEACHER:
			//tabwidget->addTab(new LessonTabTeacher(this->pluginManager), QIcon(":/Ui/book.png"), tr("Lessons"));
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

