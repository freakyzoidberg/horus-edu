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

#include "AttendanceFrame.h"

#include <qDebug>

AttendanceFrame::AttendanceFrame(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin, int userLevel, ScheduleDataPlugin *scheduleDataPlugin, AttendanceDataPlugin *attendanceDataPlugin) : QWidget(parent), _treeDataPlugin(treeDataPlugin), _userDataPlugin(userDataPlugin), _userLevel(userLevel), _scheduleDataPlugin(scheduleDataPlugin), _attendanceDataPlugin(attendanceDataPlugin)
{
        layout = new QHBoxLayout(this);
        layout->setSpacing(0);
        layout->setMargin(0);
        list = new ListUser(this, treeDataPlugin, userDataPlugin, userLevel);
        layout->addWidget(list);
        edit = 0;
        show = 0;
        connect(list, SIGNAL(AddAttendance(TreeData *, UserData *)), this, SLOT(attendanceAdded(TreeData *, UserData *)));
        connect(list, SIGNAL(ShowAttendance(TreeData *, UserData *)), this, SLOT(attendanceShowed(TreeData *, UserData *)));
}

AttendanceFrame::~AttendanceFrame()
{
        if (edit)
        {
                disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
                delete edit;
        }
        else
                disconnect(list, SIGNAL(AddAttendance(TreeData *, UserData *)), this, SLOT(attendanceAdded(TreeData *, UserData *)));
        delete list;
        delete layout;
}

void		AttendanceFrame::attendanceAdded(TreeData *node, UserData *user)
{
        disconnect(list, SIGNAL(AddAttendance(TreeData *, UserData *)), this, SLOT(attendanceAdded(TreeData *, UserData *)));
        list->hide();
        edit = new AddAttendance(this, node, user,  _scheduleDataPlugin, _attendanceDataPlugin);
        layout->addWidget(edit);
        connect(edit, SIGNAL(exit()), this, SLOT(editExited()));
}

void		AttendanceFrame::attendanceShowed(TreeData *node, UserData *user)
{
        disconnect(list, SIGNAL(ShowAttendance(TreeData *, UserData *)), this, SLOT(attendanceShowed(TreeData *, UserData *)));
        list->hide();
        show = new ShowAttendance(this, user, _attendanceDataPlugin);
        layout->addWidget(show);
        connect(show, SIGNAL(exit()), this, SLOT(showExited()));
}


void		AttendanceFrame::editExited()
{
        disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
        delete edit;
        edit = 0;
        list->show();
        connect(list, SIGNAL(AddAttendance(TreeData *, UserData *)), this, SLOT(attendanceAdded(TreeData *, UserData *)));
}

void		AttendanceFrame::showExited()
{
        disconnect(show, SIGNAL(exit()), this, SLOT(showExited()));
        delete show;
        show = 0;
        list->show();
        connect(list, SIGNAL(AddAttendance(TreeData *, UserData *)), this, SLOT(attendanceShowed(TreeData *, UserData *)));
}
