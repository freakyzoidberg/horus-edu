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
#include		"EventSmallDisplayable.h"

#include		<QLabel>
#include		<QWidget>
#include		<QFrame>
#include		<QList>
#include		<QBoxLayout>

#include "../../../../Common/EventDataPlugin.h"
#include "../../../../Common/EventData.h"

const QString	EventSmallDisplayable::pluginName() const
{
	return ("EventSmallDisplayable");
}

const QString	EventSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*EventSmallDisplayable::getWidget()
{// FAKE
	/*QWidget		*widget;
	QBoxLayout	*layout;
	QWidget		*subWidget;

	widget = new QWidget();
	layout = new QBoxLayout(QBoxLayout::TopToBottom, widget);
	subWidget = new QFrame(widget);
	new QLabel("Monday 24/11  11h00 : ENGLISH LESSON", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Monday 24/11  14h00 : SPORT", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Tuesday 25/11  10h00 : MATHEMATICS", subWidget);
	layout->addWidget(subWidget);
	return (widget); */
	// FIN FAKE

	//not fake

	QWidget		*widget = new QWidget();
	QVBoxLayout	*layout = new QVBoxLayout(widget);
	QLabel	*text;
	QList<EventData*>	*userEvents;

	text = new QLabel(tr("Trucs a faire:"));
	//usersEvent = _events->userEvents(user, QDateTime(date, QTime(0, 0, 0, 0)),
		//							QDateTime(date, QTime(23, 59, 0, 0)));
	layout->addWidget(text);
	for (int i = 0; i < userEvents->size(); ++i)
	{
		//text = new QLabel(userEvents->at(i)->node()->name());


		//layout->addWidget(text);

	}
	//(UserData* user, const QDateTime from = QDateTime(), const QDateTime to = QDateTime())


	return widget;
	//fin not fake
}

const QString	EventSmallDisplayable::getDisplayableName() const
{
	return (tr("Incomming events"));
}

QIcon			EventSmallDisplayable::getIcon() const
{
	return (QIcon(":/agenda.png"));
}
