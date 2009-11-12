#ifndef ADDEVENTWIDGET_H
#define ADDEVENTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QTextEdit>

#include "../../../../Common/EventData.h"
#include "../../../../Common/EventDataPlugin.h"

class AddEventWidget : public QWidget
{
    Q_OBJECT

public:
                    AddEventWidget();

    //accessors
    QPushButton     *cancel()       { return _cancel; }
    QPushButton     *save()         { return _save; }
    QComboBox       *monthCombo()   { return _monthCombo; }
    QComboBox       *dayCombo()     { return _dayCombo; }
    QLineEdit       *yearEdit()     { return _yearEdit; }
    QComboBox       *hours()        { return _hours; }
    QComboBox       *minutes()      { return _minutes; }
    QLineEdit       *subject()      { return _subject; }
    QLineEdit       *place()        { return _place; }
    QTextEdit       *description()  { return _description; }

    void            initDayCombo();
    void            initMonthCombo();
    void            initYearEdit();
    void            initHours();
    void            initMinutes();

private:
    EventData       *_event;

    QPushButton     *_cancel;
    QPushButton     *_save;

    //date
    QComboBox       *_monthCombo;
    QComboBox       *_dayCombo;
    QLineEdit       *_yearEdit;

    //hour
    QComboBox       *_hours;
    QComboBox       *_minutes;

    //description
    QLineEdit       *_subject;
    QLineEdit       *_place;
    QTextEdit       *_description;
};

#endif // ADDEVENTWIDGET_H
