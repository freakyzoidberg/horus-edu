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

#include "EditScheduleEvent.h"
#include "EditException.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/TreeData.h"

EditScheduleEvent::EditScheduleEvent(PluginManager *pluginManager, TreeData *node, int id)
{
    _pM = pluginManager;
    setupUi();
    fillForm(node, id);
}

void    EditScheduleEvent::fillForm(TreeData *node, int id)
{
    ScheduleData *sd = _pM->findPlugin<ScheduleDataPlugin* >()->schedule(node);
    startTime->setTime(sd->scheduleEvents().at(id)->getHStart());
    endTime->setTime(sd->scheduleEvents().at(id)->getHEnd());
    fillLessons(node);
    bool found = false;
    for (int i = 0; i < nameEdit->count(); i++)
    {
        if (nameEdit->itemText(i) == sd->scheduleEvents().at(id)->getName())
        {
            found = true;
            nameEdit->setCurrentIndex(i);
        }
    }
    if (found == false)
    {
        nameEdit->addItem(sd->scheduleEvents().at(id)->getName());
        nameEdit->setCurrentIndex(nameEdit->count() - 1);
    }
    //nameEdit->setText(sd->scheduleEvents().at(id)->getName());
    details->setText(sd->scheduleEvents().at(id)->getDetails());
    setTeacher(sd->scheduleEvents().at(id)->getTeacher());
    setDay(sd->scheduleEvents().at(id)->getJWeek());
    force->setChecked(sd->scheduleEvents().at(id)->getForce());
    modulo->setValue(sd->scheduleEvents().at(id)->getModulo());
    startDate->setDate(sd->scheduleEvents().at(id)->getSDate());
    endDate->setDate(sd->scheduleEvents().at(id)->getEDate());
    setColor(sd->scheduleEvents().at(id)->getColor());
}


EditScheduleEvent::EditScheduleEvent(PluginManager *pluginManager, TreeData *td)
{
    _pM = pluginManager;
    setupUi();
    fillLessons(td);
}

void    EditScheduleEvent::fillLessons(TreeData *td)
{
    foreach(Data *d, _pM->findPlugin<TreeDataPlugin *>()->allDatas())
    {
        TreeData *ud = qobject_cast<TreeData *>(d);
        if (ud->type() == "SUBJECT" && ud->isDescendantOf(td) == true)
        {
            nameEdit->addItem(ud->name(), ud->id());
        }
    }

}

void    EditScheduleEvent::setupUi()
{
    mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    QLabel *title = new QLabel(tr("Informations du cour"), this);
    title->setProperty("isFormTitle", true);
    mainLayout->addWidget(title);
    informationLayout = new QGridLayout();
    informationLayout->setSpacing(4);
    informationLayout->setMargin(8);
    informationLayout->setColumnMinimumWidth(0, 150);
    QLabel *nameLabel = new QLabel(tr("Nom :"), this);
    nameEdit = new QComboBox(this);
    nameEdit->setEditable(true);
    informationLayout->addWidget(nameLabel, 0, 0);
    informationLayout->addWidget(nameEdit, 0, 1);
    mainLayout->addLayout(informationLayout);


    eventFrame = new QFrame();
    eventFrame->setProperty("isFormFrame", true);
    QBoxLayout *eventMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, eventFrame);
    eventMainLayout->setSpacing(0);
    eventMainLayout->setMargin(0);
    QGridLayout *personnalBottomLayout = new QGridLayout();
    personnalBottomLayout->setSpacing(4);
    personnalBottomLayout->setMargin(8);
    personnalBottomLayout->setColumnMinimumWidth(0, 150);
    QLabel *label = new QLabel(tr("Heure de debut : "), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 0, 0, 1, 1);
    startTime = new EdtTimer(eventFrame);
    startTime->setTimeRange(QTime(7,0,0,0), QTime(19,0,0,0));
    startTime->setTime(QTime(12,0,0,0));
    personnalBottomLayout->addWidget(startTime, 0, 1, 1, 1);
    label = new QLabel(tr("Heure de fin :"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 1, 0, 1, 1);
    endTime = new EdtTimer(eventFrame);
    endTime->setTime(QTime(12,0,0,0));
    endTime->setTimeRange(QTime(7,0,0,0), QTime(19,0,0,0));
    personnalBottomLayout->addWidget(endTime, 1, 1, 1, 1);

    label = new QLabel(tr("Professeur :"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 0, 2);
    teacherList = new QComboBox(eventFrame);
    fillTeacher();
    personnalBottomLayout->addWidget(teacherList, 0, 3);
    label = new QLabel(tr("Jour :"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 1, 2);
    dayList = new QComboBox(eventFrame);
    dayList->addItem(tr("Lundi"), 1);
    dayList->addItem(tr("Mardi"), 2);
    dayList->addItem(tr("Mercredi"), 3);
    dayList->addItem(tr("Jeudi"), 4);
    dayList->addItem(tr("Vendredi"), 5);
    dayList->addItem(tr("Samedi"), 6);
    dayList->addItem(tr("Dimanche"), 7);
    personnalBottomLayout->addWidget(dayList, 1, 3);
    label = new QLabel(tr("Details"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 5, 0);
    details = new QTextEdit(eventFrame);
    personnalBottomLayout->addWidget(details, 5, 1, 1, 3);
    label = new QLabel(tr("Couleurs"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 4, 0, 1, 1);
    couleursList = new QComboBox(this);
    couleursList->addItem(tr("White"));
    couleursList->addItem(tr("Yellow"));
    couleursList->addItem(tr("Green"));
    couleursList->addItem(tr("Blue"));
    couleursList->addItem(tr("Red"));
    couleursList->setItemData(0,Qt::white,Qt::BackgroundRole);
    couleursList->setItemData(1,Qt::yellow,Qt::BackgroundRole);
    couleursList->setItemData(2,Qt::green,Qt::BackgroundRole);
    couleursList->setItemData(3,Qt::blue,Qt::BackgroundRole);
    couleursList->setItemData(4,Qt::red,Qt::BackgroundRole);


    personnalBottomLayout->addWidget(couleursList, 4, 1, 1, 1);
    label = new QLabel(tr("Une semaine sur deux :"), eventFrame);
    label->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(label, 2, 2);
    /* FIX FOR V1 */
    label->hide();
    /* END FIX FOR V1 */
    modulo = new QSpinBox(eventFrame);
    modulo->setMinimum(1);
    modulo->setMaximum(2);
    personnalBottomLayout->addWidget(modulo, 2, 3, 1, 1);
    force = new QCheckBox(tr("Appliquer le cour meme en cas de vacances"), eventFrame);
    personnalBottomLayout->addWidget(force, 2, 0, 1, 1);

    QLabel *startlabel = new QLabel(tr("Date de debut"), eventFrame);
    startlabel->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(startlabel, 3, 0);
    startDate = new QDateEdit(eventFrame);
    startDate->setCalendarPopup(true);
    startDate->setDate(QDate::currentDate());
    personnalBottomLayout->addWidget(startDate, 3, 1);

    QLabel *endlabel = new QLabel(tr("Date de fin"), eventFrame);
    endlabel->setProperty("isFormLabel", true);
    personnalBottomLayout->addWidget(endlabel, 3, 2);
    endDate = new QDateEdit(eventFrame);
    endDate->setCalendarPopup(true);
    endDate->setDate(QDate::currentDate());
    personnalBottomLayout->addWidget(endDate, 3, 3);


    personnalBottomLayout->setColumnStretch(0, 1);
    personnalBottomLayout->setColumnStretch(1, 2);
    personnalBottomLayout->setColumnStretch(2, 1);
    personnalBottomLayout->setColumnStretch(3, 2);
    eventMainLayout->addLayout(personnalBottomLayout);

    mainLayout->addWidget(eventFrame);
    //mainLayout->addWidget(new EditException());


    /* FIX FOR V1 */

    modulo->hide();
    force->hide();
    startlabel->hide();
    startDate->hide();
    endlabel->hide();
    endDate->hide();
    /* END FIX FOR v1 */
}

void    EditScheduleEvent::fillTeacher()
{
    foreach(Data *d, _pM->findPlugin<UserDataPlugin *>()->allDatas())
    {
        UserData *ud = qobject_cast<UserData *>(d);
        if (ud->level() == LEVEL_TEACHER)
        {
            teacherList->addItem(ud->name(), ud->id());
        }
    }

}

void    EditScheduleEvent::setTeacher(int teacher)
{
    for (int i = 0; i < teacherList->count(); i++)
    {
        if (teacherList->itemData(i).toInt() == teacher)
        {
            teacherList->setCurrentIndex(i);
            return;
        }
    }
}


void    EditScheduleEvent::setColor(QString color)
{
    for (int i = 0; i < couleursList->count(); i++)
    {
        if (couleursList->itemText(i) == color)
        {
            couleursList->setCurrentIndex(i);

            return;
        }
    }
}


void    EditScheduleEvent::setDay(int day)
{
    dayList->setCurrentIndex(day - 1);
}

