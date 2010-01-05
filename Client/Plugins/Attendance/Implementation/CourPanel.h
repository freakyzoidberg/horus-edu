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

#ifndef COURPANEL_H
#define COURPANEL_H

#include <QWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QWidget>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QListView>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QComboBox>
#include <QtGui/QCalendarWidget>
#include <QListView>
#include <QDateEdit>
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/AttendanceData.h"


class InfosLesson
{
    public:
        InfosLesson(/*QString n, QTime s, QTime e, bool st*/)
        {
//            name = n, start = s, end = e, state = st;
        }
        QCheckBox   *state;
        QTimeEdit   *start;
        QTimeEdit   *end;
        QLineEdit   *name;
};

class CourPanel : public QWidget
{
    Q_OBJECT

    public:
        CourPanel(ScheduleData *schedule, QDate date, AttendanceDataPlugin *attendanceDataPlugin, UserData *user);
        QVBoxLayout     *checkBoxs;
        AttendanceDataPlugin *_attendanceDataPlugin;
        UserData        *_user;
        QVBoxLayout     *nameBoxs;
        QHBoxLayout     *courLayout;
        //QLabel          *coursName;
        QCheckBox       *checkState;
        QLineEdit       *courseName;
        QTimeEdit       *sTime;
        QTimeEdit       *eTime;
        QDate           _dateAtt;
        QCheckBox       *absenceCheck;
        QList<InfosLesson *> lessonList;
   private:
        void            getScheduleLesson(ScheduleData *schedule, int day);
        void            addLesson();
        QGridLayout     *lessonBottomLayout;
        QBoxLayout      *lessonMainLayout;
};

#endif // COURPANEL_H
