#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QThread>

//! Class managing the settings of the client
/*!
 *  This class run on its own thread.
 *  Make configuration file if it don't exists.
 *  Load new configuration from the server.
 */
class ConfigManager : public QThread
{
    Q_OBJECT

public:
    //! Constructor
    /*!
     *  Initialize and start the thread.
     *  \param parent the parent of ConfigManager
     */
    ConfigManager(QObject *parent = 0);
    //! Overload of the event method
    /*!
     *  Request new config from server when received a StartEvent
     *  Send config to server when received a StopEvent
     *  Send a StartEvent to Loader when config is successfully loaded.
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
    //! Load the config from the server
    void    loadConfig();
    //! Save the config to the server
    void    saveConfig();
};

#endif // CONFIGMANAGER_H
