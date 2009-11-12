#include		"ExampleSmallDisplayable.h"

#include		<QLabel>

const QString	ExampleSmallDisplayable::pluginName() const
{
	return ("ExampleSmallDisplayable");
}

const QString	ExampleSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*ExampleSmallDisplayable::getWidget()
{
	return (new QLabel(tr("This is an example widget, you can drag & drop me !")));
}

const QString	ExampleSmallDisplayable::getDisplayableName() const
{
	return (tr("Example Widget"));
}

QIcon			ExampleSmallDisplayable::getIcon() const
{
	return (QIcon(":/Pictures/icon"));
}
