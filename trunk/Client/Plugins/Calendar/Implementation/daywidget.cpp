#include <QDebug>

#include "daywidget.h"

DayWidget::DayWidget(QDate & date, int startHour) : QWidget()
{
    _date = date;
    _startHour = startHour;
}

void     DayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int hour;
    int mousePos;
    int hourSize;

    AddEventWindows::AddEventWindowsInstance()->setGeometry(event->globalX(),
                                                            event->globalY() - 120,
                                                            260, 120);

    mousePos = event->pos().y();

    qDebug() << "posY:" << mousePos / 10;
    hour = (mousePos * 100) / this->size().height();
    hour /= 10;

    AddEventWindows::AddEventWindowsInstance()->setDate(_date, hour + this->_startHour);
    AddEventWindows::AddEventWindowsInstance()->show();
}
