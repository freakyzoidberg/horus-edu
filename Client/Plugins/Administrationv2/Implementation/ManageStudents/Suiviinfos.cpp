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
#include "Suiviinfos.h"

SuiviInfos::SuiviInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);


    suivi = new QTextEdit();

    QLabel *label = new QLabel(tr("Suivi post ecoline"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(suivi, 2, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

SuiviInfos::SuiviInfos(UserData *d)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    suivi = new QTextEdit();
    suivi->setPlainText(d->followUp());



    QLabel *label = new QLabel(tr("Suivi post ecoline"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(suivi, 2, 1);
    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
