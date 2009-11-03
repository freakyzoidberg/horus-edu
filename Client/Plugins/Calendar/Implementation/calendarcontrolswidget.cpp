#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

#include "calendarcontrolswidget.h"
#include "CalendarMainFrame.h"

CalendarControlsWidget::CalendarControlsWidget()
{
     _monthly = new QPushButton(tr("Month"));
     _daily = new QPushButton(tr("Day"));
     _weekly = new QPushButton(tr("Week"));
     _planning = new QPushButton(tr("Planning"));

     QComboBox  *dayCombo = new QComboBox;
     for (int day = 1; day <= 31; ++day)
         dayCombo->addItem(QString("Date"));

     QComboBox *monthCombo = new QComboBox;
     for (int month = 1; month <= 12; ++month)
         monthCombo->addItem(QDate::longMonthName(month));

     QComboBox  *groupList = new QComboBox;
     QComboBox  *userList = new QComboBox;
     QPushButton *go = new QPushButton(tr("Rechercher"));
     QLineEdit  *userName = new QLineEdit;
     _addEvent = new QPushButton("add an event");

     QDateTimeEdit *yearEdit = new QDateTimeEdit;
     yearEdit->setDisplayFormat("yyyy");
     yearEdit->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));

     monthCombo->setCurrentIndex(selectedDate.month() - 1);
     yearEdit->setDate(selectedDate);

     connect(monthCombo, SIGNAL(activated(int)), this, SLOT(setMonth(int)));
     connect(yearEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setYear(QDate)));

     QGridLayout *controlsLayout = new QGridLayout;

     controlsLayout->addWidget(monthCombo, 0, 0);
     controlsLayout->addWidget(dayCombo, 0, 1);
     controlsLayout->addWidget(yearEdit, 0, 2);
     controlsLayout->addWidget(_addEvent, 0, 3);

     controlsLayout->addWidget(groupList, 1, 0);
     controlsLayout->addWidget(userList, 1, 1);
     controlsLayout->addWidget(userName, 2, 0);
     controlsLayout->addWidget(go, 2, 1);

     controlsLayout->addWidget(_monthly, 2, 3);
     controlsLayout->addWidget(_daily, 2, 4);
     controlsLayout->addWidget(_weekly, 2, 5);
     controlsLayout->addWidget(_planning, 2, 6);

     this->setLayout(controlsLayout);

}

void CalendarControlsWidget::setMonth(int month)
{
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
}

 void CalendarControlsWidget::setYear(QDate date)
{
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
}


