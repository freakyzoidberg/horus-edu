#ifndef				__MAILSMALLDISPLAYABLE_H__
# define			__MAILSMALLDISPLAYABLE_H__

# include			"../../MainFrame/SmallDisplayablePlugin.h"

class				MailSmallDisplayable : public SmallDisplayablePlugin
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
