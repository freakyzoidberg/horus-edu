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
#include		"TaskSmallDisplayable.h"

#include		<QLabel>
#include		<QWidget>
#include		<QFrame>
#include		<QBoxLayout>

const QString	TaskSmallDisplayable::pluginName() const
{
	return ("TaskSmallDisplayable");
}

const QString	TaskSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*TaskSmallDisplayable::getWidget()
{// FAKE
	QWidget		*widget;
	QBoxLayout	*layout;
	QWidget		*subWidget;

	widget = new QWidget();
	layout = new QBoxLayout(QBoxLayout::TopToBottom, widget);
	subWidget = new QFrame(widget);
	new QLabel("History Homework due on  24/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Prepare Physics Exam for  25/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Geographic Homework due on  27/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Prepare English Exam for  28/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("English speak due on  30/11", subWidget);
	layout->addWidget(subWidget);
	return (widget);
}// FIN FAKE

const QString	TaskSmallDisplayable::getDisplayableName() const
{
	return (tr("Task list"));
}

QIcon			TaskSmallDisplayable::getIcon() const
{
	return (QIcon(":/schedule_256.png"));
}
