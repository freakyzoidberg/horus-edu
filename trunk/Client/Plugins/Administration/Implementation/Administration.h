#ifndef __ADMINISTRATION_H__
# define __ADMINISTRATION_H__

# include <QEvent>
# include <QtPlugin>
# include <QObject>

# include "../../../NetworkPlugin.h"
# include "../../../DisplayablePlugin.h"

# include "AdminMainFrame.h"

class Administration : public NetworkPlugin, public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(NetworkPluginClient)
    Q_INTERFACES(DisplayablePlugin)

public:
        //! return the name of the plugin
         /*!
            \return the variable modName
         */
         const QString       pluginName() const;

         //! return the version of the plugin
         /*!
           \return the variable modVersion
         */
         const QString       pluginVersion() const;
		 void load();
		 void unload();
        void                    receivePacket(UserData* user, const PluginPacket&);
        QWidget                 *getWidget();

private:
        AdminMainFrame           *widget;

private slots:
	 void send(PluginPacket *packet);
};

#endif // ADMINISTRATION_H
