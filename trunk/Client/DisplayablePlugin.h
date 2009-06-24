#ifndef DISPLAYABLEPLUGIN_H
#define DISPLAYABLEPLUGIN_H

#include <QWidget>

#include "../Common/Plugin.h"

//! Interface optionnal for using the display
/*!
 *  Each plugin implementing this interface will be able to use the display : show and use QWidgets
 */
class DisplayablePlugin : public Plugin
{
    public:
    //! Pointer to an implementation of the interface IDisplayable
    /*!
     *  This pointer is set by the Client while loading the plugin.
     *  It let plugin access display ressources
     */
    virtual QWidget *getWidget() = 0;
    virtual void setCentralWidget(QWidget *widget) = 0;
};

Q_DECLARE_INTERFACE(DisplayablePlugin, "net.horus.Client.DisplayablePlugin/1.0");

#endif // DISPLAYABLEPLUGIN_H
