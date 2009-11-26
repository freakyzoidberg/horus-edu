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
#include "Debugger.h"

#include <QLabel>
#include <QVariant>
#include <QScrollBar>

Debugger::Debugger()
{
    text.setReadOnly(true);
    resetButton.setText(tr("Reset"));
	QObject::connect(&resetButton, SIGNAL(clicked()), &text, SLOT(clear()));

    setWindowFlags(Qt::Dialog);
    setLayout(&layout);
    setWindowTitle(tr("Horus debugger"));

	QFont font = text.font();
	font.setFixedPitch(true);
	text.setFont(font);

	layout.addWidget(&text);
	layout.addWidget(&resetButton);

	show();
}

Debugger::~Debugger()
{
    _instance = 0;
}

Debugger* Debugger::_instance = 0;
Debugger* Debugger::instance()
{
    if ( ! _instance)
        _instance = new Debugger;
    return _instance;
}

void Debugger::addDebugMessage(const QString msg)
{
	text.append(msg);
}
