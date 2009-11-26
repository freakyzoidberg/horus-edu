/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QDate>
#include <QStackedWidget>
#include <QLabel>
#include <QVector>

#include "../../../../Common/EventDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "daywidget.h"

class QTextBrowser;

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
                    CalendarWidget(EventDataPlugin *);
     void           setNbRow(unsigned int nb)       { nbRow = nb; }
     void           setNbColumn(unsigned int nb)    { nbColumn = nb; }
     void           weeklyDisplay(QDate, UserData *);

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
    QVector<DayWidget *>  columnLayout;
    EventDataPlugin     *_events;
 };

#endif // CALENDARWIDGET_H
