#include		"TaskSmallDisplayable.h"

#include		<QLabel>

const QString	TaskSmallDisplayable::pluginName() const
{
	return ("TaskSmallDisplayable");
}

const QString	TaskSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*TaskSmallDisplayable::getWidget()
{
	return (new QLabel(tr("Fill me with the task list please !")));
}

const QString	TaskSmallDisplayable::getDisplayableName() const
{
	return (tr("Task list"));
}

QIcon			TaskSmallDisplayable::getIcon() const
{
	return (QIcon(":/schedule_256.png"));
}
