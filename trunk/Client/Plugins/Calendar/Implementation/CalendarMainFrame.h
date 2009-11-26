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
#ifndef CALENDARMAINFRAME_H
#define CALENDARMAINFRAME_H

#include <QWidget>
#include <QStackedWidget>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QComboBox>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/EventDataPlugin.h"
#include "../../../../Common/EventData.h"
#include "../../../../Common/PluginManager.h"

#include "calendarcontrolswidget.h"

#include "userinformations.h"

class CalendarMainFrame : public QWidget
{
    Q_OBJECT

public:
                                CalendarMainFrame(TreeDataPlugin *,
                                                  UserDataPlugin *,
                                                  EventDataPlugin *,
                                                  PluginManager *);

    //jsais plus pkoi javais besoin de ca
    QHash<quint32, TreeData *>  getNodeOfType(QString type);
  //  CalendarWidget              *calendar();

    //accessors
    QGridLayout                 *mainLayout()       { return _mainLayout; }
    TreeDataPlugin              *tree()             { return _tree; }
    UserDataPlugin              *user()             { return _users; }
  //  QCalendarWidget             *tinyCalendar()     { return _tinyCalendar; }
   // CalendarWidget              *googleCalendar()   { return _googleCalendar; }
  //  CalendarControlsWidget      *controls()         { return _controls; }
    //AddEventWidget              *add()              { return _add; }


public slots:
    //slot to handle click on the different buttons
    void                        calendarDailyDisplay();
    void                        calendarWeeklyDisplay();
    void                        calendarMonthlyDisplay();
    void                        calendarPlanningDisplay();



    //used to check if the eventdata already exist,
    //connected to the signal created() of Data*
    void                        isCreated();

    //user selection
    void                        userSelected(int);

private:
    TreeDataPlugin              *_tree;
    UserDataPlugin              *_users;
    EventDataPlugin             *_event;
   // UserData                    *_currentUser;

    QGridLayout                 *_mainLayout;
   // QCalendarWidget             *_tinyCalendar;

    PluginManager               *_calendarPlugin;
   // CalendarControlsWidget      *_controls;


    QDate                       _selectedDate;
    bool                        _created;

};

#endif // CALENDARMAINFRAME_H
