#include <QHash>
#include <QLabel>
#include <QObject>
#include <QHashIterator>
#include <QGridLayout>
#include <QStackedWidget>

#include "CalendarMainFrame.h"

#include "../../../../Common/UserData.h"
#include "CalendarCore.h"

CalendarMainFrame::CalendarMainFrame(TreeDataPlugin *_treePlugin,
                                     UserDataPlugin *_userPlugin)
{
    _tree  = _treePlugin;
    _users = _userPlugin;
    _add = new AddEventWidget();
    _mainLayout = new QGridLayout(this);
    _tinyCalendar = new QCalendarWidget;
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
    connect(_add->cancel(), SIGNAL(clicked()), this, SLOT(cancelEventSave()));
    connect(_add->save(), SIGNAL(clicked()), this, SLOT(saveEvent()));
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

    _controls->addEvent()->show();
    _googleCalendar->show();
}
