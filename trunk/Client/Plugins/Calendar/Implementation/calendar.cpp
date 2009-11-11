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
    CalendarMainFrame *frame1 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    CalendarMainFrame *frame2 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);

    _googleCalendar = new CalendarWidget();
    QDate   date;
    _googleCalendar->weeklyDisplay(date.currentDate());
    frame1->mainLayout()->addWidget(_googleCalendar, 1, 0, 1, 3);
    
    _add = new AddEventWidget();
     frame2->mainLayout()->addWidget(_add, 1, 0, 1, 3);

    _panel->addTab(frame1, "Main view");
    _panel->addTab(frame2, "Add an event");
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
