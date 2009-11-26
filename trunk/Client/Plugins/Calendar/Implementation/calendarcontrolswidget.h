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
#ifndef CALENDARCONTROLSWIDGET_H
#define CALENDARCONTROLSWIDGET_H

#include <QWidget>
#include <QDate>
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>

class CalendarControlsWidget : public QWidget
{
    Q_OBJECT

public:
                        CalendarControlsWidget();

     /*QPushButton        *addEvent()         { return _addEvent; }
     QPushButton        *daily()            { return _daily; }
     QPushButton        *weekly()           { return _weekly; }
     QPushButton        *monthly()          { return _monthly; }
     QPushButton        *planning()         { return _planning; } */
     QComboBox          *userList()         { return _userList; }
     QComboBox          *groupList()        { return _groupList; }

     void               initGroupList();
     void               initUserList(const QString & groupType);

public slots:
     void               setMonth(int month);
     void               setYear(QDate date);

private:
     QDate              selectedDate;
     QTextBrowser       *editor;
   //  QPushButton        *_daily, *_monthly, *_weekly, *_planning, *_addEvent;

     QComboBox          *_groupList;
     QComboBox          *_userList;
     QPushButton        *_go;
     QLineEdit          *_userName;
};

#endif // CALENDARCONTROLSWIDGET_H
