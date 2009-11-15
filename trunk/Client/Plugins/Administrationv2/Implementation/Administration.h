#ifndef __ADMINISTRATION_H__
# define __ADMINISTRATION_H__

# include <QEvent>
# include <QtPlugin>
# include <QObject>

# include "../../../DisplayablePlugin.h"
#include "../../../Common/TreeData.h"
#include "../../../Common/UserData.h"
#include "../../../Common/EventData.h"

class Administration : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

   public:
        const QString       pluginName() const;
        bool                canLoad() const;
        void                load();
        const QString       pluginVersion() const;
        const QString       getDisplayableName() const;
        QWidget             *getWidget();
		int					getOrder() const;
        QIcon               getIcon() const;
    private:
        TreeDataPlugin      *treePlugin;
        UserDataPlugin      *userPlugin;
        EventDataPlugin     *eventPlugin;
};

#endif // ADMINISTRATION_H
