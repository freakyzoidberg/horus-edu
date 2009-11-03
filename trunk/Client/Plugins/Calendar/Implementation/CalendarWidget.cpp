#include "CalendarWidget.h"
#include <QtGui>
#include <QPushButton>
#include "../../../Common/EventDataPlugin.h"
#include "addeventwidget.h"

 CalendarWidget::CalendarWidget()
 {
     this->nbColumn = 7;
     this->nbRow = 10;

     mainLayout = new QGridLayout(this);

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

     mainLayout->addWidget(new QLabel(tr("lendi")), 0, 1);
     mainLayout->addWidget(new QLabel(tr("mordi")), 0, 2);
     mainLayout->addWidget(new QLabel(tr("credi")), 0, 3);
     mainLayout->addWidget(new QLabel(tr("joudi")), 0, 4);
     mainLayout->addWidget(new QLabel(tr("dredi")), 0, 5);
     mainLayout->addWidget(new QLabel(tr("sadi")), 0, 6);
     mainLayout->addWidget(new QLabel(tr("gromanche")), 0, 7);

     QVector<QWidget *> columnLayout;
     for (int j = 1; j <= nbRow; ++j)
         for (int i = 1; i <= nbColumn; ++i)
        {
            AddEventWidget *tmp = new AddEventWidget();
            mainLayout->addWidget(tmp, j, i);
        }
 }
