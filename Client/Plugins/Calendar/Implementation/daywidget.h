#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDate>

#include "addeventwindows.h"

class DayWidget : public QWidget
{
    Q_OBJECT

public:
    DayWidget(QDate &, int);

protected:
     void     mouseReleaseEvent(QMouseEvent *event);

private:
    AddEventWindows     *fastAddEvent;
    QDate               _date;
    int                 _startHour;

};

#endif // DAYWIDGET_H
