#ifndef __ADMINISTRATION_H__
# define __ADMINISTRATION_H__

# include <QEvent>
# include <QtPlugin>
# include <QObject>

# include "../../../DisplayablePlugin.h"

class Administration : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

   public:
        const QString       pluginName() const;
        bool                canLoad() const;
        const QString       pluginVersion() const;
        const QString       getDisplayableName() const;
        QWidget             *getWidget();
		int					getOrder() const;
        QIcon               getIcon() const;
};

#endif // ADMINISTRATION_H
