#ifndef __COURSE_H__
# define __COURSE_H__

# include <QtPlugin>
# include <QWidget>

# include "../../../DisplayablePlugin.h"

class Course : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    const QString       pluginName() const;
    const QString       pluginVersion() const;
	const QString		getDisplayableName();
	bool				canLoad() const;
	void				load();
	void				unload();
    QWidget*            getWidget();

private:
    QWidget*            widget;
};

#endif // Course_H
