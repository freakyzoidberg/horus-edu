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
#ifndef CALENDAR_H
#define CALENDAR_H

#include <QIcon>
#include <QString>
#include <QHash>
#include <QCalendarWidget>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/EventData.h"
#include "../../../../Common/EventDataPlugin.h"
#include "../../../DisplayablePlugin.h"

#include "CalendarMainFrame.h"
#include "panel.h"
#include "addeventwidget.h"
#include "CalendarWidget.h"
#include "calendarcontrolswidget.h"
#include "userinformations.h"

class Calendar : public DisplayablePlugin
{
Q_OBJECT
Q_INTERFACES(DisplayablePlugin)

public:
                            Calendar();
    const QString           pluginName() const;
    QWidget                 *getWidget();
    const QString           pluginVersion() const;
    QIcon                   getIcon() const;
    void                    load();

    inline const QString    getDisplayableName() const { return "Calendar"; }

 public slots:
     //called when a clicked on the tiny calendar occurs
    void                    dateChanged();

    //called when the current tab changed
    void                    tabChanged(int);

    //called when the button of addEventWidget are pushed
    void                    cancelEventSave();
    void                    saveEvent();

    void                    userSelected(int index);
    void               selectGroup(int index);
     void               selectUser(int index);

private:
    TreeDataPlugin          *treePlugin;
    UserDataPlugin          *userPlugin;
    EventDataPlugin         *eventPlugin;
    Panel                   *_panel;
    CalendarWidget          *_googleCalendar;
    AddEventWidget          *_add;
    QCalendarWidget         *_tinyCalendar;
    int                     _currentIndex, _oldIndex;
    QVector<CalendarMainFrame *> frames;
    CalendarControlsWidget      *_controls;
    UserInformations            *_visibleUser;
    UserData                *_currentUser;
};

#endif // CALENDAR_H
