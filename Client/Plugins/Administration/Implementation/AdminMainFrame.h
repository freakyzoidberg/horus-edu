#ifndef				ADMINMAINFRAME_H
# define			ADMINMAINFRAME_H

# include			<QTabWidget>
# include                       "../../../../Common/EventDataPlugin.h"
# include			"../../../../Common/TreeDataPlugin.h"
# include			"../../../../Common/UserDataPlugin.h"

class				AdminMainFrame : public QTabWidget
{
    Q_OBJECT

public:
    AdminMainFrame(TreeDataPlugin *_treePlugin, UserDataPlugin *_userPlugin,  EventDataPlugin *event);
};

#endif//			ADMINMAINFRAME_H
