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

#ifndef ATTENDANCEFRAME_H
#define ATTENDANCEFRAME_H

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
#include <QSortFilterProxyModel>
#include "UserPerClass.h"
#include "ListUser.h"
#include "AddAttendance.h"
#include "ShowAttendance.h"

class				AttendanceFrame : public QWidget
{
        Q_OBJECT

public:
        AttendanceFrame(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin, int userLevel, ScheduleDataPlugin *scheduleDataPlugin, AttendanceDataPlugin *attendanceDataPlugin);
        ~AttendanceFrame();

private:
        TreeDataPlugin	*_treeDataPlugin;
        UserDataPlugin	*_userDataPlugin;
        ScheduleDataPlugin *_scheduleDataPlugin;
        AttendanceDataPlugin *_attendanceDataPlugin;
        int				_userLevel;
        ListUser		*list;
        AddAttendance		*edit;
        ShowAttendance          *show;
        QHBoxLayout		*layout;

private slots:
        void			attendanceAdded(TreeData *node, UserData *user);
        void			attendanceShowed(TreeData *node, UserData *user);
        void			editExited();
        void			showExited();
};

//class AttendanceFrame : public QWidget
//{
//    Q_OBJECT
//
//    public:
//        AttendanceFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event);
//    private:
//        QDateEdit           *dateAttendance;
//        QHBoxLayout         *absLayout;
//        QHBoxLayout         *buttonLayout;
//        QVBoxLayout         *leftSide;
//        QGridLayout         *rightSide;
//        QLineEdit           *userName;
//        QComboBox           *classList;
//        QListView           *userList;
//        QCheckBox           *allCourse;
//        QPushButton         *okButton;
//        QList<CourPanel *>  courList;
//        QSortFilterProxyModel *proxyModel;
//        void                setupUi();
//        void                fillClass(TreeDataPlugin *tree);
//        void                fillCourse(EventDataPlugin *event);
//        UserDataPlugin      *user;
//    private slots:
//        void                nameChanged(const QString &text);
//        void                classChanged( int index );
//        void                okClicked();
//        void                dChanged(const QDate &);
//        void                allChecked(int);
//};

#endif // AttendanceFRAME_H
