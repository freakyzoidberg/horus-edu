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

    mainLayout->addWidget(new QLabel(tr("Date:")), 0, 0);
    mainLayout->addWidget(_dayCombo, 0, 1);
    mainLayout->addWidget(_monthCombo, 0, 2);
    mainLayout->addWidget(_yearEdit, 0, 3);

    mainLayout->addWidget(new QLabel(tr("Starting hour:")), 1, 0);
    mainLayout->addWidget(_hours, 1, 1);
    mainLayout->addWidget(_minutes, 1, 2);
    mainLayout->addWidget(new QLabel(tr("Duration:")), 1, 3);

    mainLayout->addWidget(new QLabel(tr("Title:")), 2, 0);
    mainLayout->addWidget(_subject, 2, 1);

    mainLayout->addWidget(new QLabel(tr("Place:")), 3, 0);
    mainLayout->addWidget(_place, 3, 1);

    mainLayout->addWidget(new QLabel(tr("Descrption:")), 4, 0);
    mainLayout->addWidget(_description, 4, 1, 1, 5);

    mainLayout->addWidget(_save, 6, 7);
    mainLayout->addWidget(_cancel, 6, 8);
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
        _monthCombo->addItem(QDate::longMonthName(month));
}

void            AddEventWidget::initYearEdit()
{
    _yearEdit = new QLineEdit;
}

void            AddEventWidget::initHours()
{
    _hours = new QComboBox;
    QStringList hours;

    for (int i = 0; i <= 23; ++i)
    {
        QVariant tmp(i);
        hours.append(tmp.toString() + "h");
    }
    _hours->addItems(hours);
}

void            AddEventWidget::initMinutes()
{
    _minutes = new QComboBox;

    QStringList minutes;

    for (int i = 0; i < 60; i += 15)
    {
        QVariant tmp(i);
        minutes.append(tmp.toString() + "min");
    }
    _minutes->addItems(minutes);
}
