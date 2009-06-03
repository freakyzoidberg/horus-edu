#ifndef IDISPLAYABLEPLUGIN_H
#define IDISPLAYABLEPLUGIN_H

#include "IDisplayable.h"

//! Interface optionnal for using the display
/*!
 *  Each plugin implementing this interface will be able to use the display : show and use QWidgets
 */
class IDisplayablePlugin
{
    public:
    //! Pointer to an implementation of the interface IDisplayable
    /*!
     *  This pointer is set by the Client while loading the plugin.
     *  It let plugin access display ressources
     */
    IDisplayable    *display;
};

Q_DECLARE_INTERFACE(IDisplayablePlugin, "net.horus.Client.DisplayableInterface/1.0");

#endif // IDISPLAYABLEPLUGIN_H
