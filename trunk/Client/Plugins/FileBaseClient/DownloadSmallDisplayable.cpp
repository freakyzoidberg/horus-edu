#include		"DownloadSmallDisplayable.h"
#include                "TransfertList.h"
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
        return (new TransfertList);
}

const QString	DownloadSmallDisplayable::getDisplayableName() const
{
	return (tr("Current dowloads"));
}

QIcon			DownloadSmallDisplayable::getIcon() const
{
	return (QIcon(":/Icons/application-msword.png"));
}
