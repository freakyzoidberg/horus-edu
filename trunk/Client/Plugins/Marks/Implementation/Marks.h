#ifndef				__MARKS_H__
# define			__MARKS_H__

# include			"../../../DisplayablePlugin.h"

class				Marks : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();
};

#endif