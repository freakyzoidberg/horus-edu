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

CalendarMainFrame::CalendarMainFrame(TreeDataPlugin *_treePlugin,
                                     UserDataPlugin *_userPlugin,
                                     EventDataPlugin *_eventPlugin)
{
    _tree  = _treePlugin;
    _users = _userPlugin;
    _event = _eventPlugin;
    _created = false;

    _add = new AddEventWidget();
    _mainLayout = new QGridLayout(this);
    _tinyCalendar = new QCalendarWidget;
    _tinyCalendar->setGridVisible(true);

    _tinyCalendar->adjustSize();
    _mainLayout->addWidget(_tinyCalendar, 0, 0, 1, 1);

    QHash<quint32, TreeData *> *groups = CalendarCore::CalendarCoreInstance()->getNodeOfType("GROUP");
    QStringList userlist = CalendarCore::CalendarCoreInstance()->usersName(groups);
    //combo->addItems(userlist);

    _googleCalendar = calendar();
    _mainLayout->addWidget(_add, 1, 0, 1, 2);
    _mainLayout->addWidget(_googleCalendar, 1, 0, 1, 2);

    _controls = new CalendarControlsWidget();
    _mainLayout->addWidget(_controls, 0, 1);
    _mainLayout->setColumnStretch(1, 1);
    _mainLayout->setRowStretch(1, 1);

    connect(_controls->addEvent(), SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(_controls->daily(), SIGNAL(clicked()), this, SLOT(calendarDailyDisplay()));
    connect(_controls->monthly(), SIGNAL(clicked()), this, SLOT(calendarMonthlyDisplay()));
    connect(_controls->weekly(), SIGNAL(clicked()), this, SLOT(calendarWeeklyDisplay()));
    connect(_controls->planning(), SIGNAL(clicked()), this, SLOT(calendarPlanningDisplay()));

    connect(_add->cancel(), SIGNAL(clicked()), this, SLOT(cancelEventSave()));
    connect(_add->save(), SIGNAL(clicked()), this, SLOT(saveEvent()));
   // connect(_add->_);
    _add->setVisible(false);
}

CalendarWidget *CalendarMainFrame::calendar()
{
    return new CalendarWidget();
}

void            CalendarMainFrame::addEvent()
{
    _googleCalendar->hide();
    _controls->addEvent()->hide();

    _add->show();
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
    _add->description()->show();
}

void            CalendarMainFrame::cancelEventSave()
{
    _add->hide();

    _controls->addEvent()->show();
    _googleCalendar->show();
}

void            CalendarMainFrame::saveEvent()
{
    _add->hide();
    QDateTime   eventDate;

    EventData *userEvent = this->_event->nodeEvent(240);
    connect(userEvent, SIGNAL(created()), this, SLOT(isCreated()));  

    if (_created)
        userEvent->save();
    else
        userEvent->create();

 //   eventDate.addYears(_add->)

    _created = false;
    _controls->addEvent()->show();
    _googleCalendar->show();
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

 }

 void   CalendarMainFrame::calendarMonthlyDisplay()
 {

 }

 void   CalendarMainFrame::calendarPlanningDisplay()
 {

 }
