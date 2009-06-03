#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QThread>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QDir>
#include "IClientPlugin.h"
#include "INetworkPlugin.h"
#include "IDisplayablePlugin.h"
#include "IFilePlugin.h"
#include "ClientApplication.h"

//! Class managing the plugins of the Client
/*!
 *  This class run in its own thread.
 *  This class find the plugin directory.
 *  Load / Unload the plugins when requested.
 *  Manage dependencies.
 *  Keep a list of the plugins.
 */
class PluginManager : public QThread
{
    Q_OBJECT

public:
    //! Constuctor
    /*!
     *  Initialize and start the thread
     *  \param parent the parent ClientApplication
     */
    PluginManager(ClientApplication *parent = 0);
    //! Overload of the event method
    /*!
     *  Unload the plugins when receive a StopEvent
     *  Load  the plugins when receive a StartEvent
     *  Send an StartEvent to Loader when plugins are completely loaded.
     *  \param event the event received
     *  \return the accept status of the event
     */
    bool    event(QEvent *event);
    //! Find a loaded plugin
    /*!
     *  This method provide an access to each loaded plugins
     *  \param name The name of the plugin requested
     *  \return A pointer to the plugin requested or NULL if not found
     */
    IClientPlugin *findPlugin(QString &name) const;
    //! Find a loaded network plugin
    /*!
     *  This method provide an access to each loaded  network plugins
     *  \param name The name of the plugin requested
     *  \return A pointer to the plugin requested or NULL if not found
     */
    INetworkPlugin *findNetworkPlugin(QString &name) const;
    //! Find a loaded displayable plugin
    /*!
     *  This method provide an access to each loaded displayable plugins
     *  \param name The name of the plugin requested
     *  \return A pointer to the plugin requested or NULL if not found
     */
    IFilePlugin *findFilePlugin(QString &name) const;
    //! Find a loaded plugin using files
    /*!
     *  This method provide an access to each loaded plugins using files
     *  \param name The name of the plugin requested
     *  \return A pointer to the plugin requested or NULL if not found
     */
    IDisplayablePlugin *findDisplayablePlugin(QString &name) const;
protected:
    //! The entry point of the thread
    /*!
     *  This method just call the event loop exec()
     */
    void    run();

private:
    //! Load every needed plugins
    /*!
     *  This method find the plugin directory,
     *  and call loadPlugin for each plugin to load
     */
    void    loadPlugins();
    //! Load a specific plugin
    /*!
     *  Load the plugin identified by its name in the given path
     *  Manage dependencies, with recursively calls
     *  Add successfully loaded plugins in the plugin list
     *  Send an PluginLoadedEvent for each successfull load
     *  \param pluginName The name of the plugin to load
     *  \param userPath The user path where is the plugin to load
     *  \param systemPath The system path where is the plugin to load if not found in the user path
     *  \return A boolean indicating the success
     */
    bool    loadPlugin(QString pluginName, QDir userPath, QDir systemPath);

private:
    //! The list of loaded plugins
    QMap<QString, IClientPlugin *>    pluginsList;
    //! The list of network plugins
    QMap<QString, INetworkPlugin *>    networkPluginsList;
    //! The list of displayable plugins
    QMap<QString, IDisplayablePlugin *>    displayablePluginsList;
    //! The list of plugins using files
    QMap<QString, IFilePlugin *>    filePluginsList;
    //! The parent ClientApplication used to send events
    ClientApplication *parent;
};

#endif // PLUGINMANAGER_H
