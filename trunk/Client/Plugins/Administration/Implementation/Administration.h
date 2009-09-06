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
        //! return the name of the plugin
         /*!
            \return the variable modName
         */
        const QString       pluginName() const;
        bool                    canLoad() const;
        void                    load();
        void                    unload();
         //! return the version of the plugin
         /*!
           \return the variable modVersion
         */
        const QString       pluginVersion() const;
        const QString       getDisplayableName();
        QWidget             *getWidget();

private:
        AdminMainFrame           *widget;
};

#endif // ADMINISTRATION_H
