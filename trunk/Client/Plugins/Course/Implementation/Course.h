#ifndef __COURSE_H__
# define __COURSE_H__

# include <QtPlugin>
# include <QWidget>
# include <QHash>
# include <QString>

# include "../../../DisplayablePlugin.h"
# include "../../../../Common/PluginManager.h"
# include "../../../../Common/TreeDataPlugin.h"
# include "../../../../Common/UserData.h"
# include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"

class Course : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    const QString       pluginName() const;
    const QString       pluginVersion() const;
    const QString		getDisplayableName() const;
	int					getOrder() const;
	QIcon				getIcon() const;
    bool				canLoad() const;
    void				load();
    void				unload();
    QWidget*            getWidget();

private:
	void				createWidget();

    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
	WhiteBoardDataPlugin* whiteboardPlugin;
	QHash<QString, IDocumentController *> _controllers;
	UserData			*user;
	QWidget				*widget;

private slots:
	void				userUpdate();
};

#endif // Course_H
