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
#include <QPushButton>
#include <QGridLayout>
#include <QVariant>

#include "addeventwindows.h"

AddEventWindows    *AddEventWindows::_instance = NULL;

AddEventWindows::AddEventWindows() : QDockWidget()
{
    setFloating(true);
    setFeatures(QDockWidget::DockWidgetClosable);
    setMaximumSize(260, 120);
    setMinimumSize(260, 120);

    this->_windowTitle = new QLabel(tr(" Add an event."), this);
    _windowTitle->setGeometry(0, 10, 100, 20);

    this->_date = new QLabel(this);
    this->_date->setGeometry(46, 25, 210, 20);

    this->_dateTitle = new QLabel(tr("Date:"), this);
    _dateTitle->setGeometry(2, 25, 45, 20);

    this->_title = new QLineEdit(this);
    _title->setGeometry(45, 46, 200, 20);

    this->_titleLabel = new QLabel(tr("Title:"), this);
    _titleLabel->setGeometry(2, 46, 46, 20);

    this->_details = new Label(tr("View event's details."), this);
    _details->setGeometry(2, 68, 240, 20);

    this->_save = new QPushButton(tr("OK"), this);
    _save->setGeometry(220, 90, 30, 20);
}


AddEventWindows    *AddEventWindows::AddEventWindowsInstance()
{
   if (!_instance)
     _instance = new AddEventWindows();
   return _instance;
}

void    AddEventWindows::setDate(QDate & date, int hour)
{
    QVariant hourS(hour);

    QVariant hourE;

    if (hour + 1 == 24)
        hourE.setValue(0);
    else
        hourE.setValue(hour + 1);

    //ex : Mon 02 Dec, 15h00 - 16h00
   _date->setText(date.toString("ddd dd MMM, " + hourS.toString() + ":00 - "
                                + hourE.toString() + ":00"));
}


