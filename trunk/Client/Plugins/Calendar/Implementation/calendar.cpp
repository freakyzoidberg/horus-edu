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
    this->_oldIndex = 0;

     _currentUser = pluginManager->currentUser();


    this->_visibleUser = new UserInformations();
    _visibleUser->setInformations(_currentUser);
//_mainLayout->addWidget(_visibleUser, 0, 1, 1, 1);

    _tinyCalendar = new QCalendarWidget();
    _tinyCalendar->setGridVisible(true);
    _tinyCalendar->adjustSize();

    _controls = new CalendarControlsWidget();

    CalendarMainFrame *frame0 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    frames.insert(0, frame0);
    frame0->mainLayout()->addWidget(_tinyCalendar, 0, 0, 1, 1);
    frame0->mainLayout()->addWidget(_visibleUser, 0, 1, 1, 1);
    frame0->mainLayout()->addWidget(_controls, 0, 2);

    frame0->mainLayout()->setColumnStretch(1, 1);
    frame0->mainLayout()->setRowStretch(1, 1);

    _googleCalendar = new CalendarWidget();
    QDate date;
    _googleCalendar->weeklyDisplay(date.currentDate());
    frame0->mainLayout()->addWidget(_googleCalendar, 1, 0, 1, 3);
    connect(_controls->groupList(), SIGNAL(activated(int)), this, SLOT(selectGroup(int)));
    connect(_controls->userList(), SIGNAL(activated(int)), this, SLOT(userSelected(int)));

    CalendarMainFrame *frame1 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    _add = new AddEventWidget(); 
    frame1->mainLayout()->addWidget(_add, 1, 0, 1, 3);
    frames.insert(1, frame1);
    frame1->mainLayout()->setColumnStretch(1, 1);
    frame1->mainLayout()->setRowStretch(1, 1);

    CalendarMainFrame *frame2 = new CalendarMainFrame(this->treePlugin,
                                                     this->userPlugin,
                                                     this->eventPlugin,
                                                     this->pluginManager);
    CalendarWidget *temp = new CalendarWidget();
    temp->weeklyDisplay(date.currentDate());
    frame2->mainLayout()->addWidget(temp, 1, 0, 1, 3);
    frames.insert(2, frame2);

     frame2->mainLayout()->setColumnStretch(1, 1);
    frame2->mainLayout()->setRowStretch(1, 1);

    _panel->addTab(frame0, QIcon(":/schedule_256.png"), "Main view");
    _panel->addTab(frame1, QIcon(":/addEvent.png"), "Add an event");
    _panel->addTab(frame2, QIcon(":/schedule_256.png"), "Temp view");

    _currentIndex = _panel->currentIndex();
    connect(_panel, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(_tinyCalendar, SIGNAL(selectionChanged()), this, SLOT(dateChanged()));
    connect(_add->cancel(), SIGNAL(clicked()), this, SLOT(cancelEventSave()));
    connect(_add->save(), SIGNAL(clicked()), this, SLOT(saveEvent()));

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

    frames.value(_currentIndex)->mainLayout()->removeWidget(_visibleUser);
    frames.value(index)->mainLayout()->addWidget(_visibleUser, 0, 1, 1, 1);

    frames.value(_currentIndex)->mainLayout()->removeWidget(_controls);
    frames.value(index)->mainLayout()->addWidget(_controls, 0, 2);

    AddEventWindows::AddEventWindowsInstance()->hide();
    _oldIndex = _currentIndex;
    _currentIndex = index;
 }

 void   Calendar::cancelEventSave()
 {
     _panel->setCurrentIndex(_oldIndex);
 }

 void            Calendar::saveEvent()
{
    EventData *userEvent = eventPlugin->newEvent(_currentUser->node(), _add->subject()->text(), _currentUser);

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
    userEvent->setEndTime(begin);
    userEvent->create();
    _panel->setCurrentIndex(_oldIndex);
}

  void   Calendar::userSelected(int index)
 {
    _currentUser = this->userPlugin->user(_controls->userList()->itemData(index).toInt());
    _visibleUser->setInformations(_currentUser);
 }

  void               Calendar::selectGroup(int index)
  {
    QVariant    tmp;
    int         group_id;

    tmp = _controls->groupList()->itemData(index);
    group_id = tmp.toInt();

    //empty the user list
    _controls->userList()->clear();

    //recup all users, search them where node == group_id
    QHash<quint32, UserData *>  *users = CalendarCore::CalendarCoreInstance()->usersName("ALL");
    QHashIterator<quint32, UserData *> i(*users);

    while (i.hasNext())
    {
        i.next();
        if ((i.value()->status() != Data::EMPTY)
            && ((i.value()->node()->id() == group_id)
                || (group_id == -1)))
            _controls->userList()->addItem(i.value()->name() + " "
                               + i.value()->surname(), QVariant(i.value()->id()));
    }
    delete users;
  }

void    Calendar::selectUser(int index)
{
    QVariant    tmp;
    int         user_id;

    tmp = _controls->userList()->itemData(index);
    user_id = tmp.toInt();
}
