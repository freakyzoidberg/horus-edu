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

#include "EditSchedule.h"

EditSchedule::EditSchedule(ScheduleDataPlugin *sd, TreeDataPlugin *td, int id, int type)
{
    sdp = sd;
    tdp = td;
	mainLayout = new QVBoxLayout(this);
   mainLayout->setSpacing(0);
        mainLayout->setMargin(0);

    QLabel *title = new QLabel(tr("Dates de l\'emploi du temps"), this);
    title->setProperty("isFormTitle", true);
	title->setMaximumHeight(30);
    mainLayout->addWidget(title);

//classListView->setMaximumHeight(64);
    QFrame *eventFrame = new QFrame();
    eventFrame->setProperty("isFormFrame", true);
    QBoxLayout *eventMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, eventFrame);
    eventMainLayout->setSpacing(0);
    eventMainLayout->setMargin(0);

	datesLayout = new QGridLayout();
    datesLayout->setSpacing(4);
    datesLayout->setMargin(8);
    QLabel *startlabel = new QLabel(tr("Date de debut"), this);
	startlabel->setMaximumHeight(30);
    startlabel->setProperty("isFormLabel", true);
    datesLayout->addWidget(startlabel, 0, 0);
    _startDate = new QDateEdit(this);
    _startDate->setCalendarPopup(true);
    _startDate->setDate(QDate::currentDate());
	datesLayout->addWidget(_startDate, 1, 0);

    QLabel *endlabel = new QLabel(tr("Date de fin"), this);
    endlabel->setProperty("isFormLabel", true);
	endlabel->setMaximumHeight(30);
	datesLayout->addWidget(endlabel, 0, 1);

    _endDate = new QDateEdit(this);
    _endDate->setCalendarPopup(true);
    _endDate->setDate(QDate::currentDate());

	datesLayout->addWidget(_endDate, 1, 1);
	eventMainLayout->addLayout(datesLayout);
    mainLayout->addWidget(eventFrame);

	QLabel *t = new QLabel(tr("Ajout des vacances"), this);
	t->setMaximumHeight(30);
	t->setProperty("isFormTitle", true);
	mainLayout->addWidget(t);

    if (type == 1)
        fillForm(id);

	EditException *edit = new EditException();
	mainLayout->addWidget(edit);
	mainLayout->addWidget(new QWidget());
}

void    EditSchedule::fillForm(int id)
{
    ScheduleData *sd = sdp->schedule(tdp->node(id));
    _startDate->setDate(sd->startDate());
    _endDate->setDate(sd->endDate());
}


