#ifndef				__NEWS_H__
# define			__NEWS_H__

# include			"../../../DisplayablePlugin.h"

class				News : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
	const QString	pluginName() const;
	const QString	pluginVersion() const;
	QWidget			*getWidget();
        const QString       getDisplayableName() const;
                int					getOrder() const;
        QIcon               getIcon() const;

        bool                canLoad() const;
        void                load();

};

#endif
