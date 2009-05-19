#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QThread>
#include <QByteArray>

#include "ClientApplication.h"

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
    ConfigManager(ClientApplication *parent = 0);
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
    //! Create a basic configuration
    /*!
     *  If first launch of the application, create a basic configuration.
     */
    void    createConfig();
    //! Send the packet get settings to the server
    void    sendLoadConfig();
    //! Receive the packet settings from the server
    /*!
     *  /param data the packet received
     */
    void    recvLoadConfig(QByteArray data);
    //! Save the config to the server
    void    saveConfig();
    //! the parent CLientApplication
    ClientApplication *parent;
};

#endif // CONFIGMANAGER_H
