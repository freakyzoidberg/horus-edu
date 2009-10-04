#include		"News.h"

const QString	News::pluginName() const
{
	return ("News");
}

const QString	News::pluginVersion() const
{
	return ("0.1");
}

QWidget			*News::getWidget()
{
	return (0);
}
