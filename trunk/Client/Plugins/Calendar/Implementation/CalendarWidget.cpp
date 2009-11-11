#include "CalendarWidget.h"
#include <QtGui>
#include <QPushButton>
#include <QVariant>
#include <QColor>
#include "../../../../Common/EventDataPlugin.h"
#include "addeventwidget.h"

 CalendarWidget::CalendarWidget()
 {
     this->nbColumn = 7;
     this->nbRow = 10;
     this->currentDispType = WEEKLY;
     currentStartHour = _08AM;
     mainLayout = new QGridLayout(this);

     initHours();
     initDays();
 }

 void       CalendarWidget::weeklyDisplay(QDate date)
 {
    this->nbColumn = 7;
    this->nbRow = 10;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    for (int i = 0; i < 10; ++i)
        mainLayout->addWidget(this->hours->value(i + currentStartHour), i + 1, 0);

    mainLayout->setColumnStretch(0, 0);
    date = date.addDays(-1 * date.dayOfWeek() + 1);

    for (int i = 0; i < 7; ++i)
     {
        QString tmp = days->at(i)->text();
        if (tmp.length() > 4)
            tmp.chop(tmp.length() - 4);

        days->value(i)->setText(tmp + date.toString("dd/MM"));

        if (date == date.currentDate())
        {
            days->value(i)->setText(days->value(i)->text() + tr("(Today)"));
           /* days->value(i)->setAutoFillBackground(true);
            QPalette newPalette;
            newPalette.setColor(QPalette::Background, Qt::blue);
            days->value(i)->setPalette(newPalette); */
        }

         mainLayout->addWidget(days->value(i), 0, i + 1);

         DayWidget *tmpWidget = new DayWidget(date, this->currentStartHour);
         QGridLayout *tmpLay = new QGridLayout(tmpWidget);
         mainLayout->addWidget(tmpWidget, 1, i + 1, 10, 1);
         columnLayout.append(tmpWidget);

         date = date.addDays(1);
     }

     for (int i = 1; i <= 7; ++i)
        mainLayout->setColumnStretch(i, 1);
 }

 void   CalendarWidget::initHours(void)
 {
    this->hours = new QVector<QLabel *>(24);

    for (int i = 0; i <= 23; ++i)
    {
        QVariant    tmp(i);
        this->hours->insert(i, new QLabel(tmp.toString() + ":00"));
        this->hours->value(i)->setAlignment(Qt::AlignTop);
    }
 }

 void   CalendarWidget::initDays(void)
 {
    this->days = new QVector<QLabel *>(7);

    this->days->insert(0, new QLabel(tr("Mon ")));
    this->days->value(0)->setAlignment(Qt::AlignCenter);

    this->days->insert(1, new QLabel(tr("tue ")));
    this->days->value(1)->setAlignment(Qt::AlignCenter);

    this->days->insert(2, new QLabel(tr("Wen ")));
    this->days->value(2)->setAlignment(Qt::AlignCenter);

    this->days->insert(3, new QLabel(tr("Thu ")));
    this->days->value(3)->setAlignment(Qt::AlignCenter);

    this->days->insert(4, new QLabel(tr("Fri ")));
    this->days->value(4)->setAlignment(Qt::AlignCenter);

    this->days->insert(5, new QLabel(tr("Sat ")));
    this->days->value(5)->setAlignment(Qt::AlignCenter);

    this->days->insert(6, new QLabel(tr("Sun ")));
    this->days->value(6)->setAlignment(Qt::AlignCenter);
 }
