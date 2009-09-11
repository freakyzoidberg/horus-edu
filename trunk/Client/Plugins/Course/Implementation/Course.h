#ifndef __COURSE_H__
# define __COURSE_H__

# include <QtPlugin>
# include <QWidget>

# include "../../../DisplayablePlugin.h"
# include "../../../../Common/PluginManager.h"
# include "../../../../Common/TreeDataPlugin.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"

class Course : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    const QString       pluginName() const;
    const QString       pluginVersion() const;
    const QString	getDisplayableName();
    bool		canLoad() const;
    void		load();
    void		unload();
    QWidget*            getWidget();

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
    FileDataPlugin	*filePlugin;
};

#endif // Course_H
