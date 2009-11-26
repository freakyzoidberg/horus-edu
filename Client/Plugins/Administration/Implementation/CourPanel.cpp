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


CourPanel::CourPanel(QString cName)
{
    setupUi(cName);
    connect(absenceCheck, SIGNAL(stateChanged(int)), this, SLOT(absChecked(int)));
    connect(lateCheck, SIGNAL(stateChanged(int)), this, SLOT(retardChecked(int)));
}

void    CourPanel::setupUi(QString cName)
{
    this->setMaximumSize(1000, 55);
    courLayout = new QHBoxLayout(this);
    checkBoxs = new QVBoxLayout();
    nameBoxs = new QVBoxLayout();
    coursName = new QLabel(cName);
    nameBoxs->addWidget(coursName, 1, Qt::AlignLeft);
    courLayout->addLayout(nameBoxs, 2);
    absenceCheck = new QCheckBox("Absence");
    checkBoxs->addWidget(absenceCheck, 1, Qt::AlignLeft);
    lateCheck = new QCheckBox("Retard");
    checkBoxs->addWidget(lateCheck, 1, Qt::AlignLeft);
    courLayout->addLayout(checkBoxs, 1);
}

void    CourPanel::retardChecked(int state)
{

}

void    CourPanel::absChecked(int state)
{

}
