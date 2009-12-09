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

#ifndef EDITSCHEDULEEVENT_H
#define EDITSCHEDULEEVENT_H

#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QDateEdit>
#include <QBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/ScheduleDataPlugin.h"

class EditScheduleEvent : public QWidget
{
    Q_OBJECT

    public:
        EditScheduleEvent(PluginManager *pluginManager, TreeData *node, int id);
        EditScheduleEvent(PluginManager *pluginManager);
        inline QTime                getStart() {return(startTime->time());}
        inline void                 setStart(QTime time) {startTime->setTime(time);}
        inline QTime                getEnd() {return(endTime->time());}
        inline void                 setEnd(QTime time) {endTime->setTime(time);}
        inline QString              getName() {return(nameEdit->text());}
        inline void                 setName(QString name) {nameEdit->setText(name);}
        inline QString              getDetail() {return(details->toPlainText());}
        inline void                 setDetail(QString detail) {details->setText(detail);}
        inline int                  getDay() {return(dayList->itemData(dayList->currentIndex()).toInt());}
        inline int                  getTeacher() {return(teacherList->itemData(teacherList->currentIndex()).toInt());}
        inline int                  getModulo() {return(modulo->value());}
        inline bool                 getForce() {return(force->isChecked());}
        inline QDate                getStartDate() {return(startDate->date());}
        inline QDate                getEndDate() {return(endDate->date());}
        void                        setTeacher(int teacher);
        void                        setDay(int day);
    private:
        PluginManager       *_pM;
        QFrame              *eventFrame;
        QComboBox           *teacherList;
        QComboBox           *dayList;
        QBoxLayout          *mainLayout;
        QLineEdit           *nameEdit;
        QTimeEdit           *startTime;
        QTimeEdit           *endTime;
        QDateEdit           *startDate;
        QDateEdit           *endDate;
        QTextEdit           *details;
        QGridLayout         *informationLayout;
        QGridLayout         *exceptionLayout;
        QCheckBox           *force;
        QSpinBox            *modulo;
        void                setupUi();
        void                fillTeacher();
        void                fillForm(TreeData *node, int id);
};

#endif // EDITSCHEDULEEVENT_H
