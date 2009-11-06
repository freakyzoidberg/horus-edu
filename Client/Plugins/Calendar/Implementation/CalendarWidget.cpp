#include "CalendarWidget.h"
#include <QtGui>
#include <QPushButton>
#include <QVariant>
#include "../../../../Common/EventDataPlugin.h"
#include "addeventwidget.h"

 CalendarWidget::CalendarWidget()
 {
     this->nbColumn = 7;
     this->nbRow = 10;
     bite = NULL;
     mainLayout = NULL;
 }

 void       CalendarWidget::weeklyDisplay(QDate date)
 {
    if (mainLayout)
        delete mainLayout;
    if (bite)
        delete bite;
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(new QLabel, 0, 0);

     mainLayout->addWidget(new QLabel(tr("8:00")), 1, 0);
     mainLayout->addWidget(new QLabel(tr("9:00")), 2, 0);
     mainLayout->addWidget(new QLabel(tr("10:00")), 3, 0);
     mainLayout->addWidget(new QLabel(tr("11:00")), 4, 0);
     mainLayout->addWidget(new QLabel(tr("12:00")), 5, 0);
     mainLayout->addWidget(new QLabel(tr("13:00")), 6, 0);
     mainLayout->addWidget(new QLabel(tr("14:00")), 7, 0);
     mainLayout->addWidget(new QLabel(tr("15:00")), 8, 0);
     mainLayout->addWidget(new QLabel(tr("16:00")), 9, 0);
     mainLayout->addWidget(new QLabel(tr("17:00")), 10, 0);

     date = date.addDays(-1 * date.dayOfWeek() + 1);

     bite = new QLabel(tr("Mon") + date.toString(" d/MM"));
     mainLayout->addWidget(bite, 0, 1);
     mainLayout->addWidget(new QLabel(tr("mordi")), 0, 2);
     mainLayout->addWidget(new QLabel(tr("credi")), 0, 3);
     mainLayout->addWidget(new QLabel(tr("joudi")), 0, 4);
     mainLayout->addWidget(new QLabel(tr("dredi")), 0, 5);
     mainLayout->addWidget(new QLabel(tr("sadi")), 0, 6);
     mainLayout->addWidget(new QLabel(tr("gromanche")), 0, 7);

     QVector<QWidget *> columnLayout;
     for (int i = 1; i <= nbColumn; ++i)
     {
         QWidget *tmp = new QWidget();
         QGridLayout *tmpLay = new QGridLayout(tmp);
         mainLayout->addWidget(tmp, 2, i, 10, 1);
         columnLayout.append(tmp);
     }
 }
