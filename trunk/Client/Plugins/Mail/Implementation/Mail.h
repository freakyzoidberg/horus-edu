#ifndef				__MAIL_H__
# define			__MAIL_H__

# include			"../../../DisplayablePlugin.h"

class				Mail : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();

};

#endif
