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
#ifndef ADDEVENTWIDGET_H
#define ADDEVENTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QTextEdit>

#include "../../../../Common/EventData.h"
#include "../../../../Common/EventDataPlugin.h"

class AddEventWidget : public QWidget
{
    Q_OBJECT

public:
                    AddEventWidget();

    //accessors
    QPushButton     *cancel()       { return _cancel; }
    QPushButton     *save()         { return _save; }
    QComboBox       *monthCombo()   { return _monthCombo; }
    QComboBox       *dayCombo()     { return _dayCombo; }
    QLineEdit       *yearEdit()     { return _yearEdit; }
    QComboBox       *hours()        { return _hours; }
    QComboBox       *minutes()      { return _minutes; }
    QLineEdit       *subject()      { return _subject; }
    QLineEdit       *place()        { return _place; }
    QTextEdit       *description()  { return _description; }
    QComboBox       *hoursDur()     { return _durHour; }
    QComboBox       *minutesDur()   { return _durMinutes; }

    void            initDayCombo();
    void            initMonthCombo();
    void            initYearEdit();
    void            initHours();
    void            initMinutes();
    void            initDurHour();
    void            initDurMinutes();

private:
    EventData       *_event;

    QPushButton     *_cancel;
    QPushButton     *_save;

    //date
    QComboBox       *_monthCombo;
    QComboBox       *_dayCombo;
    QLineEdit       *_yearEdit;

    //hour
    QComboBox       *_hours;
    QLabel          *_hoursLabel;
    QComboBox       *_minutes;
    QLabel          *_minutesLabel;

    //duration
    QComboBox       *_durHour;
    QLabel          *_durHourLabel;
    QComboBox       *_durMinutes;
    QLabel          *_durMinutesLabel;

    //description
    QLineEdit       *_subject;
    QLineEdit       *_place;
    QTextEdit       *_description;
};

#endif // ADDEVENTWIDGET_H
