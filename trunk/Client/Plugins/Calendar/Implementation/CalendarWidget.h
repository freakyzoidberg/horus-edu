#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QDate>
#include <QStackedWidget>
#include <QLabel>
#include <QVector>

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
     void           initHours(void);
     void           initDays(void);

     enum displayType {
       DAILY,
       WEEKLY,
       MONTHLY
     };

     enum startHour {
         _00AM = 0,
         _08AM = 8,
         _05PM = 17
     };

    unsigned int        currentDispType;
    unsigned int        currentStartHour;
    QVector<QLabel *>   *hours, *days;
    unsigned int        nbRow, nbColumn;
    QGridLayout         *mainLayout;
 };

#endif // CALENDARWIDGET_H
