#ifndef ICLIENTPLUGIN_H
#define ICLIENTPLUGIN_H

#include <QObject>
#include <QEvent>
#include <QStringList>
#include <QByteArray>

#include "IClient.h"

//! Interface needed for each plugins of the Client
/*!
 *  This interface defines some required functions for each plugins in order to be well managed by the Client.
 */
class IClientPlugin : public QObject
{
  public:
    //! Pointer to an implementation of the interface IClient
    /*!
     *  This pointer is set by the Client while loading the plugin.
     *  It let plugin access other ressources like other plugins.
     */
    IClient                     *client;
    //! The name of the plugin
    /*!
     *  This method provide the name of the plugin.
     *  Each plugin must have an unique name.
     *  \return the name of the plugin
     */
    virtual const QByteArray    getName() const = 0;
    //! The version of the plugin
    /*!
     *  This function provide the version of the plugin.
     *  The method is used in dependencies.
     *  \return the version of the plugin
     */
    virtual const QByteArray    getVersion() const = 0;
    //! The plugins conflicting with this plugin
    /*!
     *  This method provide a list of plugins which can't be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline QStringList         getPluginsConflicts() const { return QStringList(); }
    //! The plugins required with this plugin
    /*!
     *  This method provide a list of plugins which must be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline QStringList         getPluginsRequired() const { return QStringList(); }
    //! The plugins recommended with this plugin
    /*!
     *  This method provide a list of plugins which may be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline QStringList         getPluginsRecommended() { return QStringList(); }
    //! Surcharge of the method event
    /*!
     *  Each plugin must manage events that it will receive.
     *  \param event the event received
     *  \return the accept status of the event
     */
    virtual inline bool                event(QEvent*) { return false; }
};

Q_DECLARE_INTERFACE(IClientPlugin, "net.horus.Client.PluginInterface/1.0");

#endif // ICLIENTPLUGIN_H
