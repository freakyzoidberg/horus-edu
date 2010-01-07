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
 * along with Horus. If not, see <http:/Marks//www.gnu.org/licenses/>.               *
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
#include "newexams.h"

#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

NewExams::NewExams(QVBoxLayout *RightLayout)
{
	mainLayout = new QGridLayout(this);

	QLabel *title = new QLabel(tr("Creation d'un examen."), this);
	title->setProperty("isFormTitle", true);
	title->setMaximumHeight(30);
	QLabel *startlabel = new QLabel(tr("Date :"));
	startlabel->setMaximumHeight(30);
	startlabel->setProperty("isFormLabel", true);

	thedate = new QDateEdit();
	examComment = new QLineEdit();

	QLabel *thecomment = new QLabel(tr("Titre :"));
	thecomment->setMaximumHeight(30);
	thecomment->setProperty("isFormLabel", true);
	mainLayout->addWidget(title,		 0, 0, 1, 4);

	mainLayout->addWidget(startlabel,	 1, 0, 1, 1);
	mainLayout->addWidget(thedate,		 1, 1, 1, 1);
	mainLayout->addWidget(new QWidget(), 1, 2, 1, 2);

	mainLayout->addWidget(thecomment,    2, 0, 1, 1);
	mainLayout->addWidget(examComment,   2, 1, 1, 1);
	mainLayout->addWidget(new QWidget(), 2, 2, 1, 2);

	mainLayout->addWidget(new QWidget(), 3, 0, 9, 4);
	mainLayout->setColumnStretch(3, 5);
	thedate->setDate(QDate().currentDate());
}
