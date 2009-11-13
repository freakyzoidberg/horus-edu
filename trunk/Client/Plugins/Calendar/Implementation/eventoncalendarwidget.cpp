#include <QVariant>

#include "eventoncalendarwidget.h"

EventOnCalendarWidget::EventOnCalendarWidget(QWidget *dad, QTime begin, QTime end, QString title)
        : QWidget(dad)
{
  //test = new QLabel("je suis un label", this);
  layout = new QVBoxLayout(this);
  this->begin = new QLabel(QVariant(begin.hour()).toString() + "h"
                           + QVariant(begin.minute()).toString());
  this->end = new QLabel(QVariant(end.hour()).toString() + "h"
                           + QVariant(end.minute()).toString());
  this->title = new QLabel(title);
  layout->addWidget(this->title);
  layout->addWidget(this->begin);
  layout->addWidget(this->end);
}

EventOnCalendarWidget::~EventOnCalendarWidget()
{
    //delete test;
}
