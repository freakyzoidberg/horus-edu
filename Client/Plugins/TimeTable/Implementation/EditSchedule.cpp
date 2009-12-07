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
    vLayout = new QVBoxLayout(this);
    _classList = new QComboBox();
    vLayout->addWidget(_classList);
    titleLayout = new QHBoxLayout();
    QLabel *lStart = new QLabel(tr("Debut"));
    QLabel *lEnd = new QLabel(tr("Fin"));
    titleLayout->addWidget(lStart);
    titleLayout->addWidget(lEnd);
    vLayout->addLayout(titleLayout);
    hLayout = new QHBoxLayout();
    _startDate = new QCalendarWidget();
    _endDate = new QCalendarWidget();
    hLayout->addWidget(_startDate);
    hLayout->addWidget(_endDate);
    vLayout->addLayout(hLayout);
    hLayout2 = new QHBoxLayout(); 
    line = new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    hLayout2->addWidget(line, 14);
    _addException = new QPushButton("+");
    _addException->setFlat(true);
    hLayout2->addWidget(_addException, 1);
    if (type == 1)
        fillForm(id);
    vLayout->addLayout(hLayout2);
    connect(_addException, SIGNAL(clicked()), this, SLOT(addException()));
    fillClasses();
}

void    EditSchedule::fillForm(int id)
{
    ScheduleData *sd = sdp->schedule(tdp->node(id));
    _startDate->setSelectedDate(sd->startDate());
    _endDate->setSelectedDate(sd->endDate());
}

void    EditSchedule::fillClasses()
{
        QList<Data*> datas = tdp->allDatas();

        for (int i = 0, j = 0; i < datas.size(); ++i)
        {
                TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
                if (tmp->type() == "GRADE")
                {
                    _classList->addItem(tmp->name(), tmp->id());
                }
        }

}

void    EditSchedule::addException()
{

}
