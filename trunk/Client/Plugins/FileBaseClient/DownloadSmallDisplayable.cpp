#include		"DownloadSmallDisplayable.h"

#include		<QLabel>

const QString	DownloadSmallDisplayable::pluginName() const
{
	return ("DownloadSmallDisplayable");
}

const QString	DownloadSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*DownloadSmallDisplayable::getWidget()
{
	return (new QLabel(tr("Fill me with the current downloads.")));
}

const QString	DownloadSmallDisplayable::getDisplayableName() const
{
	return (tr("Current dowloads"));
}

QIcon			DownloadSmallDisplayable::getIcon() const
{
	return (QIcon(":/Icons/application-msword.png"));
}
