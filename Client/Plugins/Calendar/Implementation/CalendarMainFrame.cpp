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
