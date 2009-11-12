#ifndef				__TASKSMALLDISPLAYABLE_H__
# define			__TASKSMALLDISPLAYABLE_H__

# include			"../../MainFrame/SmallDisplayablePlugin.h"

class				TaskSmallDisplayable : public SmallDisplayablePlugin
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
