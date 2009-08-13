#ifndef CLIENTAPPLICATION_H
#define CLIENTAPPLICATION_H

#include    <QApplication>
#include    <QWidget>
#include    <QMainWindow>

//! Main class representing the application
/*!
 *  This class initalize the software, create the Loader and the MainWindow.
 *  Provide some functions for reset plugins or network.
 */
class ClientApplication : public QApplication
{
    Q_OBJECT
public:
    //! Constructor
    /*!
     *  Initialize names and version of the application.
     *  Instanciate NetworkManager and PluginManager
     *  Create MainWindow but don't show it for now
     *  Give the hand to the Loader
     *  \param argc the argc of the main function
     *  \param argv the argv of the main function
     */
    ClientApplication(int argc, char *argv[]);
    //! Destructor
    /*!
     *  Terminate each composant of the application.
     *  Because of threads we can't just call exit !
     */
    ~ClientApplication();
    //! Surcharge of the event function
    /*!
     *  Useless for now.
     *  May be deleted in the future.
     *  \param event the event received
     *  \return the accept status of the event
     */
    bool    event(QEvent *event);
    //! A pointer to the Loader Widget
    QWidget *loader;
    //! A pointer te the MainWindow Widget
    QMainWindow *mainWindow;

public slots:
    ////! Unload then load again all the plugins
    //void    reloadPlugins();
    ////! Stop then start again the network
    //void    restartNetwork();
    //! Unload everything then exit
    void    preExit();
};


#endif // CLIENTAPPLICATION_H
