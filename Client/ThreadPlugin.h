#ifndef PLUGINTHREAD_H
#define PLUGINTHREAD_H

#include <QThread>
#include <QEvent>
#include <QString>
#include <QDir>
#include "ClientApplication.h"
#include "../Common/PluginManager.h"

//! Class managing the plugins of the Client
/*!
 *  This class run in its own thread.
 *  This class find the plugin directory.
 *  Load / Unload the plugins when requested.
 *  Manage dependencies.
 *  Keep a list of the plugins.
 */
class ThreadPlugin : public QThread, public PluginManager
{
    Q_OBJECT

public:
    //! Constuctor
    /*!
     *  Initialize and start the thread
     *  \param parent the parent ClientApplication
     */
    ThreadPlugin(ClientApplication *parent = 0);
    //! Overload of the event method
    /*!
     *  Unload the plugins when receive a StopEvent
     *  Load  the plugins when receive a StartEvent
     *  Send an StartEvent to Loader when plugins are completely loaded.
     *  \param event the event received
     *  \return the accept status of the event
     */
    bool    event(QEvent *event);
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
    bool    loadPlugin(QString pluginName, QDir path);
};

#endif // PLUGINTHREAD_H
