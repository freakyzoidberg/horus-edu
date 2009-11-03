#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QDate>
#include <QStackedWidget>

class QTextBrowser;

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
                    CalendarWidget();
     void           setNbRow(unsigned int nb)       { nbRow = nb; }
     void           setNbColumn(unsigned int nb)    { nbColumn = nb; }

 private:
     unsigned int   nbRow, nbColumn;
     QGridLayout    *mainLayout;
 };

#endif // CALENDARWIDGET_H
