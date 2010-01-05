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

#include "CourPanel.h"


CourPanel::CourPanel(ScheduleData *schedule, QDate date, AttendanceDataPlugin *attendanceDataPlugin, UserData *user)
{

    _attendanceDataPlugin = attendanceDataPlugin;
    _user = user;
    _dateAtt = date;
//    QFrame *lessonFrame = new QFrame(this);
//    lessonFrame->setProperty("isFormFrame", true);
    lessonMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    lessonMainLayout->setSpacing(0);
    lessonMainLayout->setMargin(0);
    QLabel *lessonTitle = new QLabel(tr("Cours informations"), this);
    lessonTitle->setProperty("isFormTitle", true);
    lessonMainLayout->addWidget(lessonTitle);
    lessonBottomLayout = new QGridLayout();
    lessonBottomLayout->setSpacing(4);
    lessonBottomLayout->setMargin(8);
    if (schedule != 0)
    {
        bool haveEvent = false;
        if (schedule->scheduleEvents().size() == 0)
        {
            addLesson();
        }
        else
        {
            for (int i = 0; i < schedule->scheduleEvents().size(); i++)
            {
                if (schedule->scheduleEvents().at(i)->getJWeek() == date.dayOfWeek())
                {
                    haveEvent = true;
                }
            }
            if (haveEvent == true)
               getScheduleLesson(schedule, date.dayOfWeek());
            else
                addLesson();
        }
    }
    else
    {
        addLesson();
    }
    lessonMainLayout->addLayout(lessonBottomLayout);
}

void    CourPanel::addLesson()
{
    QLabel *label = new QLabel(tr("Nom du Cour"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    label = new QLabel(tr("Heure Debut"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 1);
    label = new QLabel(tr("Heure Fin"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    label = new QLabel(tr("Appliquer"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 3);
    InfosLesson *tmp = new InfosLesson();
    tmp->name = new QLineEdit(this);
    lessonBottomLayout->addWidget(tmp->name, 1, 0);
    tmp->start = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->start, 1, 1);
    tmp->end = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->end, 1, 2);
    tmp->state = new QCheckBox(this);
    lessonBottomLayout->addWidget(tmp->state, 1, 3);
    tmp->state->setChecked(true);
    tmp->state->setDisabled(true);
    lessonList.append(tmp);
}

void    CourPanel::getScheduleLesson(ScheduleData *schedule, int day)
{
    QLabel *label = new QLabel(tr("Nom du Cour"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 0);
    label = new QLabel(tr("Heure Debut"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 1);
    label = new QLabel(tr("Heure Fin"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 2);
    label = new QLabel(tr("Appliquer"), this);
    label->setProperty("isFormLabel", true);
    lessonBottomLayout->addWidget(label, 0, 3);
    int idx = 0;
    for (int i = 0; i < schedule->scheduleEvents().size(); i++)
    {
        if (schedule->scheduleEvents().at(i)->getJWeek() == day)
        {
            idx++;
            InfosLesson *tmp = new InfosLesson();
            tmp->name = new QLineEdit(this);
            lessonBottomLayout->addWidget(tmp->name, idx + 1, 0);
            tmp->name->setText(schedule->scheduleEvents().at(i)->getName());
            tmp->name->setDisabled(true);
            tmp->start = new QTimeEdit(this);
            tmp->start->setTime(schedule->scheduleEvents().at(i)->getHStart());
            tmp->start->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->start, idx + 1, 1);
            tmp->end = new QTimeEdit(this);
            tmp->end->setTime(schedule->scheduleEvents().at(i)->getHEnd());
            tmp->end->setDisabled(true);
            lessonBottomLayout->addWidget(tmp->end, idx + 1, 2);
            tmp->state = new QCheckBox(this);
            lessonBottomLayout->addWidget(tmp->state, idx + 1, 3);
            lessonList.append(tmp);

        }
    }
    QList<AttendanceData *> absList = _attendanceDataPlugin->attendance(_user);
    if (absList.size() > 0)
    {
        int i = 0;
        for (i = 0; i < absList.size(); i++)
        {
            for(int j = 0; j < lessonList.size(); j++)
            {
                if (absList.at(i)->lesson() == lessonList.at(j)->name->text() &&
                    absList.at(i)->date() == _dateAtt)
                {
                    if (absList.at(i)->type() == 1)
                        lessonList.at(j)->state->setText(tr("Absent"));
                    else
                        lessonList.at(j)->state->setText(tr("Absent"));
                    lessonList.at(j)->state->setDisabled(true);
                }
            }

        }

    }
    idx++;
    InfosLesson *tmp = new InfosLesson();
    tmp->name = new QLineEdit(this);
    lessonBottomLayout->addWidget(tmp->name, idx + 1, 0);
    tmp->start = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->start,idx + 1, 1);
    tmp->end = new QTimeEdit(this);
    lessonBottomLayout->addWidget(tmp->end, idx + 1, 2);
    tmp->state = new QCheckBox(this);
    lessonBottomLayout->addWidget(tmp->state, idx + 1, 3);
    lessonList.append(tmp);
}
