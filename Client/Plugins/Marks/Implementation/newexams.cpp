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
#include "newexams.h"

#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

NewExams::NewExams(QVBoxLayout *RightLayout)
{
	mainLayout = new QVBoxLayout(this);
   mainLayout->setSpacing(0);
		mainLayout->setMargin(0);

	//QLabel *title = new QLabel(tr("Dates de l\'emploi du temps"), this);
	/* FIX FOR V1 */
	QLabel *title = new QLabel(tr("Creation d'un examen."), this);
	/* END FIX FOR v1 */
	title->setProperty("isFormTitle", true);
	title->setMaximumHeight(30);
	mainLayout->addWidget(title);

//classListView->setMaximumHeight(64);
	QFrame *eventFrame = new QFrame();
	eventFrame->setProperty("isFormFrame", true);
	QBoxLayout *eventMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, eventFrame);
	eventMainLayout->setSpacing(0);
	eventMainLayout->setMargin(0);

	QLabel *startlabel = new QLabel(tr("Date :"));
	startlabel->setMaximumHeight(30);
	startlabel->setProperty("isFormLabel", true);
	//datesLayout->addWidget(startlabel, 1, 0);

	thedate = new QDateEdit();

	examComment = new QLineEdit();
	mainLayout->addWidget(startlabel);
	mainLayout->addWidget(thedate);

	QLabel *thecomment = new QLabel(tr("Title :"));
	thecomment->setMaximumHeight(30);
	thecomment->setProperty("isFormLabel", true);
	mainLayout->addWidget(thecomment);
	mainLayout->addWidget(examComment);
	mainLayout->addWidget(new QWidget());
}
