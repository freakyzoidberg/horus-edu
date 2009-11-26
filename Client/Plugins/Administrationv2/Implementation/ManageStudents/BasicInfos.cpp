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
#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
//    QFormLayout *BasicLayout = new QFormLayout(this);
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    name = new QLineEdit(this);
    surname = new QLineEdit(this);

    bday = new QDateEdit(this);


    bplace = new QLineEdit(this);
    address = new QLineEdit(this);
    email = new QLineEdit(this);
    brosis = new QSpinBox(this);
    bday->setDisplayFormat(tr("dd/MM/yy"));
        bday->setDate(QDate::currentDate());
    bday->setCalendarPopup(true);
    QLabel *label;

    label = new QLabel(tr("Last name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(name, 0, 1,1,3);

    //BasicLayout->addRow(tr("Nom"), name);

    label = new QLabel(tr("First name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(surname, 1, 1,1,3);
    //BasicLayout->addRow(tr("Prenom"), surname);

    label = new QLabel(tr("Birthday"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(bday, 2, 1,1,3);
    //BasicLayout->addRow(tr("Date de naissance"), bday);


    label = new QLabel(tr("lieu de naissance"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(bplace, 2, 1,1,3);

    label = new QLabel(tr("Address"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 3, 0);
    BasicLayout->addWidget(address, 3, 1,1,3);
    //BasicLayout->addRow(tr("Adresse"), address);

    label = new QLabel(tr("Email"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 4, 0);
    BasicLayout->addWidget(email, 4, 1);

    label = new QLabel(tr("Brother/Sister"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 4, 2);
    BasicLayout->addWidget(brosis, 4, 3);


    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

BasicInfos::BasicInfos(UserData* ud)
{
QGridLayout *BasicLayout = new QGridLayout(this);

    setProperty("isFormFrame", true);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QDateEdit(this);
    bday->setDisplayFormat(tr("dd/MM/yy"));
    bday->setCalendarPopup(true);
    bplace = new QLineEdit(this);
    address = new QLineEdit(this);
    email = new QLineEdit(this);
    brosis = new QSpinBox(this);

    name->setText(ud->name());
    surname->setText(ud->surname());
    address->setText(ud->address());
    bday->setDate(ud->birthDate());
    bplace->setText(ud->bornPlace());
    email->setText(ud->mail());
    brosis->setValue(ud->nbrBrothers());






    QLabel *label;

    label = new QLabel(tr("Last name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(name, 0, 1,1,3);

    //BasicLayout->addRow(tr("Nom"), name);

    label = new QLabel(tr("First name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(surname, 1, 1,1,3);
    //BasicLayout->addRow(tr("Prenom"), surname);


    label = new QLabel(tr("Birthday"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(bday, 2, 1,1,3);
    //BasicLayout->addRow(tr("Date de naissance"), bday);

    label = new QLabel(tr("lieu de naissance"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(bplace, 2, 1,1,3);

    label = new QLabel(tr("Address"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 3, 0);
    BasicLayout->addWidget(address, 3, 1,1,3);
    //BasicLayout->addRow(tr("Adresse"), address);

    label = new QLabel(tr("Email"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 4, 0);
    BasicLayout->addWidget(email, 4, 1);

    label = new QLabel(tr("Brother/Sister"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 4, 2);
    BasicLayout->addWidget(brosis, 4, 3);
  BasicLayout->setColumnMinimumWidth(0,150);

    this->setLayout(BasicLayout);
}
