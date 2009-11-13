#ifndef EVENTONCALENDARWIDGET_H
#define EVENTONCALENDARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTime>

class EventOnCalendarWidget : public QWidget
{
public:
    EventOnCalendarWidget(QWidget *, QTime begin, QTime end, QString title);
    ~EventOnCalendarWidget();

private:
    //  QLabel * test;
      QVBoxLayout   *layout;
      QLabel        *title, *begin, *end;
};

#endif // EVENTONCALENDARWIDGET_H
