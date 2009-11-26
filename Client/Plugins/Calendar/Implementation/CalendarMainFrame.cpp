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
#include <QHash>
#include <QLabel>
#include <QObject>
#include <QHashIterator>
#include <QGridLayout>
#include <QStackedWidget>
#include <QTimeEdit>

#include "CalendarMainFrame.h"

#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"
#include "CalendarCore.h"
#include "addeventwindows.h"

CalendarMainFrame::CalendarMainFrame(TreeDataPlugin  *_treePlugin,
                                     UserDataPlugin  *_userPlugin,
                                     EventDataPlugin *_eventPlugin,
                                     PluginManager *_pluginManager)
{
    _tree  = _treePlugin;
    _users = _userPlugin;
    _event = _eventPlugin;
    this->_calendarPlugin = _calendarPlugin;
    _created = false;






       //  _add = new AddEventWidget();
        _mainLayout = new QGridLayout(this);
         _mainLayout->setMargin(3);
        _mainLayout->setSpacing(3);
      //  _tinyCalendar = new QCalendarWidget;
      //   _tinyCalendar->setGridVisible(true);

        // _tinyCalendar->adjustSize();
      //_mainLayout->addWidget(_tinyCalendar, 0, 0, 1, 1);


      //_googleCalendar = calendar();
      //calendarWeeklyDisplay();

     // _mainLayout->addWidget(_add, 1, 0, 1, 3);
      //_mainLayout->addWidget(_googleCalendar, 1, 0, 1, 3);



 /*  connect(_controls->addEvent(), SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(_controls->daily(), SIGNAL(clicked()), this, SLOT(calendarDailyDisplay()));
    connect(_controls->monthly(), SIGNAL(clicked()), this, SLOT(calendarMonthlyDisplay()));
    connect(_controls->weekly(), SIGNAL(clicked()), this, SLOT(calendarWeeklyDisplay()));
    connect(_controls->planning(), SIGNAL(clicked()), this, SLOT(calendarPlanningDisplay())); */



   //

 //   connect(_add->cancel(), SIGNAL(clicked()), this, SLOT(cancelEventSave()));
 //   connect(_add->save(), SIGNAL(clicked()), this, SLOT(saveEvent()));

   // connect(AddEventWindows::AddEventWindowsInstance()->details(),
     //       SIGNAL(clicked()), this, SLOT(addEvent()));
}


void        CalendarMainFrame::isCreated()
{
    _created = true;
}

 void   CalendarMainFrame::calendarDailyDisplay()
 {

 }

 void   CalendarMainFrame::calendarWeeklyDisplay()
 {
   // _googleCalendar->weeklyDisplay(_tinyCalendar->selectedDate());
 }

 void   CalendarMainFrame::calendarMonthlyDisplay()
 {

 }

 void   CalendarMainFrame::calendarPlanningDisplay()
 {

 }

 void	CalendarMainFrame::userSelected(int)
 {
 }
