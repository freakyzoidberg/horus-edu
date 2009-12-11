#ifndef EDITSCHEDULE_H
#define EDITSCHEDULE_H

#include <QWidget>
#include <QComboBox>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QDateEdit>
#include <QBoxLayout>
#include "EditException.h"
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/ScheduleDataPlugin.h"

class EditSchedule : public QWidget
{
    Q_OBJECT

    public:
        EditSchedule(ScheduleDataPlugin *sd, TreeDataPlugin *td, int id, int type);
        inline QDate                getStart() {return(_startDate->date());}
        inline void                 setStart(QDate date) {_startDate->setDate(date);}
        inline QDate                getEnd() {return(_endDate->date());}
        inline void                 setEnd(QDate date) {_endDate->setDate(date);}
    private:
        ScheduleDataPlugin          *sdp;
        TreeDataPlugin              *tdp;
        QDateEdit                   *_startDate;
        QDateEdit                   *_endDate;
		QVBoxLayout                  *mainLayout;
        QGridLayout                 *datesLayout;
        QGridLayout                 *exceptionLayout;
        void                        fillClasses();
        void                        fillForm(int id);
};

#endif // EDITSCHEDULE_H
