#ifndef								__SMALLDISPLAYABLEPLUGIN_H__
# define							__SMALLDISPLAYABLEPLUGIN_H__

# include							<QWidget>
# include							<QString>
# include							<QIcon>

# include							"../../../Common/Plugin.h"

//! Interface for using the display inside the mainboard
/*!
 *  Each plugin implementing this interface will be able to use the display inside the mainboard
 */
class								SmallDisplayablePlugin : public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

public:
    virtual QWidget					*getWidget() = 0;

    //! Return the displayable name of the plugin.
    /*!
     *  This name will be displayed in the menu.
     *  If an empty QString is returned, this plugin will not be displayed in the menu.
     */
    virtual inline const QString	getDisplayableName() const { return (QString()); }
	virtual inline QIcon			getIcon() const { return (QIcon()); }
};

Q_DECLARE_INTERFACE(SmallDisplayablePlugin, "net.horus.Client.SmallDisplayablePlugin/1.0");

#endif //							__SMALLDISPLAYABLEPLUGIN_H__
