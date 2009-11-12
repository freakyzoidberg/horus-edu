#include		"EventSmallDisplayable.h"

#include		<QLabel>

const QString	EventSmallDisplayable::pluginName() const
{
	return ("EventSmallDisplayable");
}

const QString	EventSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*EventSmallDisplayable::getWidget()
{
	return (new QLabel(tr("Fill me with the events !")));
}

const QString	EventSmallDisplayable::getDisplayableName() const
{
	return (tr("Incomming events"));
}

QIcon			EventSmallDisplayable::getIcon() const
{
	return (QIcon(":/agenda.png"));
}
