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
        const QString       getDisplayableName() const;
        QWidget             *getWidget();
        const int           getOrder() const;
    private:
            TreeDataPlugin      *treePlugin;
            UserDataPlugin      *userPlugin;
};

#endif // ADMINISTRATION_H
