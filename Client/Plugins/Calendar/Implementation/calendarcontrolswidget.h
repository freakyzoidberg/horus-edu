#ifndef CALENDARCONTROLSWIDGET_H
#define CALENDARCONTROLSWIDGET_H

#include <QWidget>
#include <QDate>
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>

class CalendarControlsWidget : public QWidget
{
    Q_OBJECT

public:
                        CalendarControlsWidget();

     /*QPushButton        *addEvent()         { return _addEvent; }
     QPushButton        *daily()            { return _daily; }
     QPushButton        *weekly()           { return _weekly; }
     QPushButton        *monthly()          { return _monthly; }
     QPushButton        *planning()         { return _planning; } */
     QComboBox          *userList()         { return _userList; }

     void               initGroupList();
     void               initUserList(const QString & groupType);

public slots:
     void               setMonth(int month);
     void               setYear(QDate date);
     void               selectGroup(int index);
     void               selectUser(int index);

private:
     QDate              selectedDate;
     QTextBrowser       *editor;
   //  QPushButton        *_daily, *_monthly, *_weekly, *_planning, *_addEvent;

     QComboBox          *_groupList;
     QComboBox          *_userList;
     QPushButton        *_go;
     QLineEdit          *_userName;
};

#endif // CALENDARCONTROLSWIDGET_H
