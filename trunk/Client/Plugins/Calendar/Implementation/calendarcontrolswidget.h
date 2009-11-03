#ifndef CALENDARCONTROLSWIDGET_H
#define CALENDARCONTROLSWIDGET_H

#include <QWidget>
#include <QDate>
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>

//#include "CalendarMainFrame.h"

class CalendarControlsWidget : public QWidget
{
    Q_OBJECT

public:
                        CalendarControlsWidget();

     QPushButton        *addEvent()                 { return _addEvent; }
public slots:
     void               setMonth(int month);
     void               setYear(QDate date);

private:
     QDate              selectedDate;
     QTextBrowser       *editor;
     QPushButton        *_daily, *_monthly, *_weekly, *_planning, *_addEvent;
     QComboBox          *dayCombo, *monthCombo;
     QDateTimeEdit      *yearEdit;
    // CalendarMainFrame  *calendar;
};

#endif // CALENDARCONTROLSWIDGET_H
