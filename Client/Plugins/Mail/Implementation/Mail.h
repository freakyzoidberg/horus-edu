#ifndef				__MAIL_H__
# define			__MAIL_H__

# include			"../../../DisplayablePlugin.h"

class				Mail : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
        const QString       pluginVersion() const;
        const QString       pluginName() const;
        QWidget             *getWidget();
        const QString       getDisplayableName() const;
        const int           getOrder() const;
        QIcon               getIcon() const;

        bool                canLoad() const;
        void                load();





};

#endif
