#ifndef				__ATTENDANCE_H__
# define			__ATTENDANCE_H__

# include			"../../../DisplayablePlugin.h"

class				Attendance : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();
};

#endif