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

    _currentUser = _pluginManager->currentUser();


        this->_visibleUser = new UserInformations();
        _visibleUser->setInformations(_currentUser);

       //  _add = new AddEventWidget();
        _mainLayout = new QGridLayout(this);
         _mainLayout->setMargin(0);
        _mainLayout->setSpacing(0);
        _tinyCalendar = new QCalendarWidget;
         _tinyCalendar->setGridVisible(true);

         _tinyCalendar->adjustSize();
      _mainLayout->addWidget(_tinyCalendar, 0, 0, 1, 1);
        _mainLayout->addWidget(_visibleUser, 0, 1, 1, 1);

      //_googleCalendar = calendar();
      calendarWeeklyDisplay();

     // _mainLayout->addWidget(_add, 1, 0, 1, 3);
      //_mainLayout->addWidget(_googleCalendar, 1, 0, 1, 3);

       _controls = new CalendarControlsWidget();
       _mainLayout->addWidget(_controls, 0, 2);
       _mainLayout->setColumnStretch(1, 1);
       _mainLayout->setRowStretch(1, 1);

 /*   connect(_controls->addEvent(), SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(_controls->daily(), SIGNAL(clicked()), this, SLOT(calendarDailyDisplay()));
    connect(_controls->monthly(), SIGNAL(clicked()), this, SLOT(calendarMonthlyDisplay()));
    connect(_controls->weekly(), SIGNAL(clicked()), this, SLOT(calendarWeeklyDisplay()));
    connect(_controls->planning(), SIGNAL(clicked()), this, SLOT(calendarPlanningDisplay())); */

    connect(_tinyCalendar, SIGNAL(selectionChanged()), this, SLOT(dateChanged()));

    connect(_controls->userList(), SIGNAL(activated(int)), this, SLOT(userSelected(int)));

 //   connect(_add->cancel(), SIGNAL(clicked()), this, SLOT(cancelEventSave()));
 //   connect(_add->save(), SIGNAL(clicked()), this, SLOT(saveEvent()));

    connect(AddEventWindows::AddEventWindowsInstance()->details(),
            SIGNAL(clicked()), this, SLOT(addEvent()));

    //_add->setVisible(false);
}

/*CalendarWidget *CalendarMainFrame::calendar()
{
    return new CalendarWidget();
} */

void            CalendarMainFrame::addEvent()
{
   // _googleCalendar->hide();
    //_controls->addEvent()->hide();
    AddEventWindows::AddEventWindowsInstance()->hide();

   /* _add->show();
    _add->cancel()->show();
    _add->save()->show();
    _add->description()->show();
    _add->dayCombo()->show();
    _add->monthCombo()->show();
    _add->yearEdit()->show();
    _add->hours()->show();
    _add->minutes()->show();
    _add->subject()->show();
    _add->place()->show();
    _add->description()->show(); */
}

void            CalendarMainFrame::cancelEventSave()
{
 //   _add->hide();

    //_controls->addEvent()->show();
   // _googleCalendar->show();
}

void            CalendarMainFrame::saveEvent()
{
   // _add->hide();

/*    EventData *userEvent = _event->newEvent(_currentUser->node(), _currentUser);

    QDateTime       begin, end, duration;
    QVariant        years(_add->yearEdit()->text()),
                    months(_add->monthCombo()->currentText()),
                    days(_add->dayCombo()->currentText()),
                    hours(_add->hours()->currentText()),
                    minutes(_add->minutes()->currentText());

    QTime           t(hours.toInt(), minutes.toInt());
    QDate           eventDay(years.toInt(), months.toInt(), days.toInt());

    begin.setDate(eventDay);
    begin.setTime(t);
    userEvent->setStartTime(begin);

    t.setHMS(1, 15, 0, 0);

    begin.addSecs(hours.toInt() * 3600 + minutes.toInt() * 60);

    duration.setTime(t);
    userEvent->setDuration(duration);

    connect(userEvent, SIGNAL(created()), this, SLOT(isCreated()));  

    _created = false;
 //   _controls->addEvent()->show();
    _googleCalendar->show(); */
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

 void   CalendarMainFrame::dateChanged()
 {
   // _googleCalendar->weeklyDisplay(_tinyCalendar->selectedDate());
 }

 void   CalendarMainFrame::userSelected(int index)
 {
    _currentUser = this->_users->user(_controls->userList()->itemData(index).toInt());
    _visibleUser->setInformations(_currentUser);
 }
