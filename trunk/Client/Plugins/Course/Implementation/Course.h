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
#ifndef __COURSE_H__
# define __COURSE_H__

# include <QtPlugin>
# include <QWidget>
# include <QHash>
# include <QString>
# include <QBoxLayout>
# include <QPushButton>

# include "../../../DisplayablePlugin.h"
# include "../../../../Common/PluginManager.h"
# include "../../../../Common/TreeDataPlugin.h"
# include "../../../../Common/UserData.h"
# include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"
# include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"

class Course : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    const QString       pluginName() const;
    const QString       pluginVersion() const;
    const QString		getDisplayableName() const;
	int					getOrder() const;
	QIcon				getIcon() const;
    bool				canLoad() const;
    void				load();
    void				unload();
    QWidget*            getWidget();

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
	WhiteBoardDataPlugin* whiteboardPlugin;
	QHash<QString, IDocumentController *> _controllers;
	UserData			*user;
	QBoxLayout			*layout;
	QWidget				*parent;
	QWidget				*widget;
	QPushButton			*back;

private slots:
	void				joinWhiteBoard(WhiteBoardData *whiteBoardData);
};

#endif // Course_H
