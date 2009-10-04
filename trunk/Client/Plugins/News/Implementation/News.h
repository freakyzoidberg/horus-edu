#ifndef				__NEWS_H__
# define			__NEWS_H__

# include			"../../../DisplayablePlugin.h"

class				News : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();
};

#endif
