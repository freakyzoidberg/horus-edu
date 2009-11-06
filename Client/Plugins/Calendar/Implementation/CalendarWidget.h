#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QDate>
#include <QStackedWidget>
#include <QLabel>

class QTextBrowser;

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
                    CalendarWidget();
     void           setNbRow(unsigned int nb)       { nbRow = nb; }
     void           setNbColumn(unsigned int nb)    { nbColumn = nb; }
     void           weeklyDisplay(QDate);

 private:
     unsigned int   nbRow, nbColumn;
     QGridLayout    *mainLayout;
     QLabel *bite;
 };

#endif // CALENDARWIDGET_H
