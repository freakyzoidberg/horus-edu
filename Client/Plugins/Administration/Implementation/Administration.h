#ifndef __ADMINISTRATION_H__
# define __ADMINISTRATION_H__

# include <QEvent>
# include <QtPlugin>
# include <QObject>

# include "../../../../Common/NetworkPlugin.h"
# include "../../../DisplayablePlugin.h"

# include "AdministrationFrame.h"

class Administration : public NetworkPlugin, public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(NetworkPlugin)
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
        AdministrationFrame           *widget;

private slots:
	 void send(PluginPacket *packet);
};

#endif // ADMINISTRATION_H
