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

#include <QIcon>
#include <QLabel>
#include <QDebug>

#include "InfoPanel.h"

InfoPanel::InfoPanel(bool node)
{
	QGridLayout *layout = new QGridLayout();

	if (node)
	{
		QLabel	*label = new QLabel();
		label->setPixmap(QPixmap(":/TimeTableOK.gif"));
		layout->addWidget(label, 0, 0);
		layout->addWidget(new QLabel(tr("time table found.")), 0, 1);
	}
	else
	{
		QLabel	*label = new QLabel();
		label->setPixmap(QPixmap(":/error.png"));
		layout->addWidget(label, 0, 0);
		layout->addWidget(new QLabel(tr("No time table.")), 0, 1);
	}
	/*if (it != 0)
	{
		layout->addWidget(new QLabel(tr("name :")), 0,0);
		layout->addWidget(new QLabel(tr("birthday :")),1,0);
		layout->addWidget(new QLabel(tr("address :")),2,0);

		QLabel *na = new QLabel(it->surname()+ " " + it->name());
		na->setWordWrap(true);
		layout->addWidget(na, 0,1);

		QLabel *bd = new QLabel(it->birthDate().toString());
		bd->setWordWrap(true);
		layout->addWidget(bd, 1,1);
		QLabel *add = new QLabel(it->address());
		add->setWordWrap(true);
		layout->addWidget(add, 2,1);
	} */
	setLayout(layout);
}
