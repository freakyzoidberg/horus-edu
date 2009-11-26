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
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QHashIterator>
#include <QPixmap>

#include "CalendarCore.h"
#include "calendarcontrolswidget.h"
#include "CalendarMainFrame.h"

CalendarControlsWidget::CalendarControlsWidget()
{
  /*   _monthly = new QPushButton(tr("Month"));
     _daily = new QPushButton(tr("Day"));
     _weekly = new QPushButton(tr("Week"));
     _planning = new QPushButton(tr("Planning"));*/

     _groupList = new QComboBox();
     initGroupList();

     _userList = new QComboBox();
     //QLabel *userLabel = new QLabel();
     //userLabel->setPixmap(QPixmap(":/user.png"));

     initUserList("ALL");

     _go = new QPushButton(tr("Rechercher"));
     _userName = new QLineEdit;

    // _addEvent = new QPushButton("add an event");

     QGridLayout *controlsLayout = new QGridLayout;
   /*  controlsLayout->setMargin(0);
     controlsLayout->setSpacing(0); */

     //controlsLayout->addWidget(_addEvent, 0, 3);

    // controlsLayout->addWidget(groupLabel, 0, 0);
     controlsLayout->addWidget(_groupList, 0, 0);
     //controlsLayout->addWidget(userLabel, 1, 0);
     controlsLayout->addWidget(_userList, 1, 0);
     controlsLayout->addWidget(_userName, 2, 0);
     controlsLayout->addWidget(_go, 2, 1);

   /*  controlsLayout->addWidget(_monthly, 2, 0);
     controlsLayout->addWidget(_daily, 2, 1);
     controlsLayout->addWidget(_weekly, 2, 2);
     controlsLayout->addWidget(_planning, 2, 3); */

     //connect combo box signals


     this->setLayout(controlsLayout);
}

void CalendarControlsWidget::setMonth(int month)
{
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
}

void CalendarControlsWidget::setYear(QDate date)
{
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
}

void CalendarControlsWidget::initGroupList()
{
	QHash<quint32, TreeData *> *groups = CalendarCore::CalendarCoreInstance()->getNodeOfType("GROUP");
	QHashIterator<quint32, TreeData *> i(*groups);
	_groupList->addItem(tr("All users."), QVariant(-1));
	while (i.hasNext())
	{
		i.next();
		_groupList->addItem(i.value()->name(), QVariant(i.value()->id()));
	}
	delete groups;
}

void CalendarControlsWidget::initUserList(const QString & groupName)
{
	foreach (UserData* user, CalendarCore::CalendarCoreInstance()->usersName(groupName))
		_userList->addItem(user->name() + " " + user->surname(), QVariant(user->id()));
}



