#ifndef				__EXAMPLESMALLDISPLAYABLE_H__
# define			__EXAMPLESMALLDISPLAYABLE_H__

# include			"../SmallDisplayablePlugin.h"

class				ExampleSmallDisplayable : public SmallDisplayablePlugin
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
