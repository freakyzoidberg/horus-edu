#include <QPushButton>
#include <QGridLayout>
#include <QVariant>
#include <QLabel>
#include <QStringList>

#include "addeventwidget.h"

#include <QDebug>

AddEventWidget::AddEventWidget()
{
    QGridLayout     *mainLayout = new QGridLayout(this);

    _cancel = new QPushButton(tr("Cancel"));

    _save = new QPushButton(tr("Save"));

    _subject = new QLineEdit;
    _place = new QLineEdit;
    _description = new QTextEdit;

    initDayCombo();
    initMonthCombo();
    initYearEdit();
    initHours();
    initMinutes();
    initDurHour();
    initDurMinutes();

    mainLayout->addWidget(new QLabel(tr("Date:")), 0, 0);
    mainLayout->addWidget(_dayCombo, 0, 1);
    mainLayout->addWidget(_monthCombo, 0, 2);
    mainLayout->addWidget(_yearEdit, 0, 3);

    mainLayout->addWidget(new QLabel(tr("Starting hour:")), 1, 0);
    mainLayout->addWidget(_hours, 1, 1);
    mainLayout->addWidget(_hoursLabel, 1, 2);

    mainLayout->addWidget(_minutes, 1, 3);
    mainLayout->addWidget(_minutesLabel, 1, 4);

    mainLayout->addWidget(new QLabel(tr("Duration:")), 1, 5);
    mainLayout->addWidget(_durHour, 1, 6);
    mainLayout->addWidget(_durHourLabel, 1, 7);
    mainLayout->addWidget(_durMinutes, 1, 8);
    mainLayout->addWidget(_durMinutesLabel, 1, 9);

    mainLayout->addWidget(new QLabel(tr("Title:")), 2, 0);
    mainLayout->addWidget(_subject, 2, 1);

    mainLayout->addWidget(new QLabel(tr("Place:")), 3, 0);
    mainLayout->addWidget(_place, 3, 1);

    mainLayout->addWidget(new QLabel(tr("Descrption:")), 4, 0);
    mainLayout->addWidget(_description, 4, 1, 1, 5);

    mainLayout->addWidget(_save, 6, 10);
    mainLayout->addWidget(_cancel, 6, 11);
}

void            AddEventWidget::initDayCombo()
{    
    _dayCombo = new QComboBox;
    QStringList days;

    for (int day = 1; day <= 31; ++day)
    {
        QVariant tmp(day);
        days.append(tmp.toString());
    }

    _dayCombo->addItems(days);
}

void            AddEventWidget::initMonthCombo()
{
    _monthCombo = new QComboBox;
    for (int month = 1; month <= 12; ++month)
        _monthCombo->addItem(QDate::longMonthName(month), QVariant(month));
}

void            AddEventWidget::initYearEdit()
{
    _yearEdit = new QLineEdit;
}

void            AddEventWidget::initHours()
{
    _hours = new QComboBox;
    _hoursLabel = new QLabel(tr("h"));
    QStringList hours;

    for (int i = 0; i <= 23; ++i)
    {
        QVariant tmp(i);
        hours.append(tmp.toString());
    }
    _hours->addItems(hours);
}

void            AddEventWidget::initMinutes()
{
    _minutes = new QComboBox;
    this->_minutesLabel = new QLabel(tr("min"));

    QStringList minutes;

    for (int i = 0; i < 60; i += 15)
    {
        QVariant tmp(i);
        minutes.append(tmp.toString());
    }
    _minutes->addItems(minutes);
}

void        AddEventWidget::initDurHour()
{
    _durHourLabel = new QLabel(tr("h"));
    _durHour = new QComboBox;
    for (int i = 0; i < 24; ++i)
    {
        QVariant tmp(i);
        _durHour->addItem(tmp.toString());
    }
}

void        AddEventWidget::initDurMinutes()
{
    _durMinutesLabel = new QLabel(tr("min"));
    _durMinutes = new QComboBox;
    for (int i = 0; i < 60; i += 15)
    {
        QVariant tmp(i);
        _durMinutes->addItem(tmp.toString());
    }
}
