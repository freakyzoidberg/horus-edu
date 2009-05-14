#ifndef CLIENTAPPLICATION_H
#define CLIENTAPPLICATION_H

#include    <QtGui/QApplication>

//! Main class representing the application
/*!
    This class initalize the software, create the Loader and the MainWindow.
    Provide some functions for reset plugins or network.
*/
class ClientApplication : public QApplication
{
public:
    //! Constructor
    /*!
        Initialize names and version of the application.
        Instanciate NetworkManager and PluginManager
        Create MainWindow but don't show it for now
        Give the hand to the Loader
    */
    ClientApplication(int argc, char *argv[]);
    //! Destructor
    /*!
        Terminate each composant of the application.
        Because of threads we can't just call exit !
        \param argc the argc of the main function
        \param argv the argv of the main function
    */
    ~ClientApplication();
    //! Surcharge of the event function
    /*!
        Useless for now.
        May be deleted in the future.
        \param event the event received
        \return the accept status of the event
    */
    bool    event(QEvent *event);
    //! Unload then load again all the plugins
    void    reloadPlugins();
    //! Stop then start again the network
    void    restartNetwork();
    //! A pointer to the Loader Widget
    QWidget *loader;
    //! A pointer te the MainWindow Widget
    QWidget *mainWindow;
};


#endif // CLIENTAPPLICATION_H
