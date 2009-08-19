#include		"Marks.h"

const QString	Marks::pluginName() const
{
	return ("Marks");
}

const QString	Marks::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Marks::getWidget()
{
	return (0);
}
