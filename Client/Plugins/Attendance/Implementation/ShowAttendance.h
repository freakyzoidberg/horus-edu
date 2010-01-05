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

#ifndef SHOWATTENDANCE_H
#define SHOWATTENDANCE_H

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
#include "CourPanel.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/AttendanceData.h"

class InfosAttendance
{
    public:
        InfosAttendance(/*QString n, QTime s, QTime e, bool st*/)
        {
//            name = n, start = s, end = e, state = st;
        }
        QLineEdit   *type;
        QDateEdit   *date;
        QTimeEdit   *start;
        QTimeEdit   *end;
        QLineEdit   *name;
        QCheckBox   *del;
};

class ShowAttendance : public QWidget
{
    Q_OBJECT

    public:
        ShowAttendance(QWidget *parent, UserData *user, AttendanceDataPlugin *attendanceDataPlugin);
    private:
        QFrame		*lessonFrame;
        QGridLayout         *lessonBottomLayout;
        QBoxLayout          *lessonMainLayout;
        QLabel		*lessonTitle;
        QWidget     *getAttendancesFrame();
        QList<InfosAttendance *> attendanceList;
        AttendanceDataPlugin *_attendanceDataPlugin;
        UserData            *_user;
    private slots:
//        void                reseted();
//        void                saved();
        void                exited();
        void                butClicked();
    signals:
        void			exit();
};

#endif // SHOWATTENDANCE_H
