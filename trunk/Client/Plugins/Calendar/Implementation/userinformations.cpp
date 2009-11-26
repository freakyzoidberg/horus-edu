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
#include <QPixmap>

#include "userinformations.h"

UserInformations::UserInformations()
{
    mainLayout = new QGridLayout(this);
    this->_title = new QLabel(tr("User's Calendar:"));
    this->_firstname = new QLabel();
    this->_name = new QLabel();
    this->_picture = new QLabel();
    this->_phone = new QLabel();

    mainLayout->addWidget(_title, 0, 0, 1, 2);
    mainLayout->addWidget(_picture, 1, 0, 3, 1);
    mainLayout->addWidget(_firstname, 1, 1, 1, 1);
    mainLayout->addWidget(_name, 2, 1, 1, 1);
    mainLayout->addWidget(_phone, 3, 1, 1, 1);
}

void    UserInformations::setInformations(UserData *user)
{
    _firstname->setText(user->name());
    _name->setText(user->surname());
    _phone->setText(user->phone1());
    _picture->setPixmap(QPixmap(":/anonymous.png")); //user->picture() qd yen aura une
}
