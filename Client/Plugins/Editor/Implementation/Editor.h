#ifndef				__EDITOR_H__
# define			__EDITOR_H__

# include			"../../../DisplayablePlugin.h"

class				Editor : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();
};

#endif