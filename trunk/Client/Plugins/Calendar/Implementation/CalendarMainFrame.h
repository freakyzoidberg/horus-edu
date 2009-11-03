#ifndef CALENDARMAINFRAME_H
#define CALENDARMAINFRAME_H

#include <QWidget>
#include <QStackedWidget>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QComboBox>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/TreeDataPlugin.h"

#include "calendar.h"
#include "CalendarWidget.h"
#include "calendarcontrolswidget.h"
#include "addeventwidget.h"

class CalendarMainFrame : public QWidget
{
    Q_OBJECT
public:
                                CalendarMainFrame(TreeDataPlugin *,
                                                  UserDataPlugin *);

    QHash<quint32, TreeData *>  getNodeOfType(QString type);
    CalendarWidget              *calendar();

    TreeDataPlugin              *tree()             { return _tree; }
    UserDataPlugin              *user()             { return _users; }
    QCalendarWidget             *tinyCalendar()     { return _tinyCalendar; }
    CalendarWidget              *googleCalendar()   { return _googleCalendar; }
    CalendarControlsWidget      *controls()         { return _controls; }

public slots:
    void                        addEvent();
    void                        cancelEventSave();
    void                        saveEvent();

private:
    TreeDataPlugin              *_tree;
    UserDataPlugin              *_users;
    QGridLayout                 *_mainLayout;
    QCalendarWidget             *_tinyCalendar;
    CalendarWidget              *_googleCalendar;
    CalendarControlsWidget      *_controls;
    AddEventWidget              *_add;
};

#endif // CALENDARMAINFRAME_H
