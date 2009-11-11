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
    CalendarControlsWidget      *controls()         { return _controls; }
    //AddEventWidget              *add()              { return _add; }


public slots:
    //slot to handle click on the different buttons
    void                        addEvent();
    void                        cancelEventSave();
    void                        saveEvent();
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
    UserData                    *_currentUser;

    QGridLayout                 *_mainLayout;
   // QCalendarWidget             *_tinyCalendar;

    PluginManager               *_calendarPlugin;
    CalendarControlsWidget      *_controls;
    UserInformations            *_visibleUser;

    QDate                       _selectedDate;
    bool                        _created;

};

#endif // CALENDARMAINFRAME_H
