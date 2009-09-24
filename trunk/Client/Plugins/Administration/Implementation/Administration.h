#ifndef __ADMINISTRATION_H__
# define __ADMINISTRATION_H__

# include <QEvent>
# include <QtPlugin>
# include <QObject>

# include "../../../DisplayablePlugin.h"

# include "AdminMainFrame.h"

class Administration : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
        const QString       pluginName() const;
        bool                canLoad() const;
        void                load();
        const QString       pluginVersion() const;
        const QString       getDisplayableName();
        QWidget             *getWidget();
        TreeDataPlugin      *treePlugin;
        UserDataPlugin      *userPlugin;
        const int           getOrder() const;
};

#endif // ADMINISTRATION_H
