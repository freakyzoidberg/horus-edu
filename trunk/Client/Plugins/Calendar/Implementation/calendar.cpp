#include <QHash>
#include <QDate>

#include "calendar.h"
#include "CalendarMainFrame.h"
#include "CalendarCore.h"
#include "panel.h"

Calendar::Calendar()
{
    treePlugin = NULL;
    userPlugin = NULL;
}

const QString   Calendar::pluginName()    const
{
    return "Calendar";
}

const QString   Calendar::pluginVersion() const
{
    return "0.001b.17/10/2009.18h19min";
}

QWidget *Calendar::getWidget()
{
    _panel =  new Panel();
    this->_currentIndex = 0;

    _tinyCalendar = new QCalendarWidget();
    _tinyCalendar->setGridVisible(true);
    _tinyCalendar->adjustSize();

    CalendarMainFrame *frame0 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    frames.insert(0, frame0);
    frame0->mainLayout()->addWidget(_tinyCalendar, 0, 0, 1, 1);
    _googleCalendar = new CalendarWidget();
    QDate date;
    _googleCalendar->weeklyDisplay(date.currentDate());
    frame0->mainLayout()->addWidget(_googleCalendar, 1, 0, 1, 3);

    CalendarMainFrame *frame1 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    _add = new AddEventWidget(); 
    frame1->mainLayout()->addWidget(_add, 1, 0, 1, 3);
    frames.insert(1, frame1);

    CalendarMainFrame *frame2 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    CalendarWidget *temp = new CalendarWidget();
    temp->weeklyDisplay(date.currentDate());
    frame2->mainLayout()->addWidget(temp, 1, 0, 1, 3);
    frames.insert(2, frame2);

    _panel->addTab(frame0, QIcon(":/schedule_256.png"), "Main view");
    _panel->addTab(frame1, QIcon(":/addEvent.png"), "Add an event");
    _panel->addTab(frame2, QIcon(":/schedule_256.png"), "Temp view");

    _currentIndex = _panel->currentIndex();
    connect(_panel, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(_tinyCalendar, SIGNAL(selectionChanged()), this, SLOT(dateChanged()));
    return _panel;
}

void Calendar::load()
{
    treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
    userPlugin = pluginManager->findPlugin<UserDataPlugin *>();
    eventPlugin = pluginManager->findPlugin<EventDataPlugin *>();

    Plugin::load();
    CalendarCore::CalendarCoreInstance(treePlugin, userPlugin);
}

QIcon   Calendar::getIcon() const
{
   return (QIcon(":/agenda.png"));
}

 void   Calendar::dateChanged()
 {
    _googleCalendar->weeklyDisplay(_tinyCalendar->selectedDate());
 }

 void   Calendar::tabChanged(int index)
 {
    frames.value(_currentIndex)->mainLayout()->removeWidget(_tinyCalendar);
    frames.value(index)->mainLayout()->addWidget(_tinyCalendar, 0, 0, 1, 1);
    _currentIndex = index;
 }
