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
#include "Parentinfos.h"
#include <QGridLayout>
#include <QLabel>
ParentInfos::ParentInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    parent = new QComboBox(this);

    QLabel *label = new QLabel(tr("Parent"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(parent, 0, 1);
	BasicLayout->setColumnStretch(1, 1);



BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


ParentInfos::ParentInfos(UserData *)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

	parent = new QComboBox(this);

    QLabel *label = new QLabel(tr("Parent"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(parent, 0, 1);
	BasicLayout->setColumnStretch(1, 1);


    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


