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
#include "formaddgrade.h"

FormAddGrade::FormAddGrade()
{
	_mainLayout = new QGridLayout(this);
	_commentLabel = new QLabel(tr("Commentaire:"));
	_commentEdit = new QTextEdit();
	_markLabel = new QLabel(tr("Note:"));
	_markEdit = new QLineEdit();
	QLabel *title = new QLabel(tr("Ajout d'une note."), this);
	title->setProperty("isFormTitle", QVariant(true));
	title->setMaximumHeight(30);

	_mainLayout->addWidget(title, 0, 0, 1, 2);
	_mainLayout->addWidget(_commentLabel, 1, 0, 1, 2);
	_mainLayout->addWidget(_commentEdit, 2, 0, 2, 2);
	_mainLayout->addWidget(_markLabel,4, 0);
	_mainLayout->addWidget(_markEdit, 4, 1);
	_mainLayout->addWidget(new QWidget(), 5, 0, 10, 2);
}
