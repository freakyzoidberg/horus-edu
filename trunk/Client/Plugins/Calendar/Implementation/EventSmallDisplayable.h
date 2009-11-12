#ifndef				__EVENTSMALLDISPLAYABLE_H__
# define			__EVENTSMALLDISPLAYABLE_H__

# include			"../../MainFrame/SmallDisplayablePlugin.h"

class				EventSmallDisplayable : public SmallDisplayablePlugin
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
