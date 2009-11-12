#ifndef				__DOWNLOADSMALLDISPLAYABLE_H__
# define			__DOWNLOADSMALLDISPLAYABLE_H__

# include			"../MainFrame/SmallDisplayablePlugin.h"

class				DownloadSmallDisplayable : public SmallDisplayablePlugin
{
	Q_OBJECT
	Q_INTERFACES(SmallDisplayablePlugin)

public:
	// Interface Plugin
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	// Interface SmallDisplayablePlugin
	QWidget			*getWidget();
	const QString	getDisplayableName() const;
	QIcon			getIcon() const;
};

#endif
