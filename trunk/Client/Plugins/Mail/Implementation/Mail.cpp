#include		"Mail.h"

const QString	Mail::pluginName() const
{
	return ("Mail");
}

const QString	Mail::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Mail::getWidget()
{
	return (0);
}
