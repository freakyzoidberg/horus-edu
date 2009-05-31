#ifndef LOADER_H
#define LOADER_H

#include <QDialog>

#include "ui_Loader.h"

class ClientApplication;

//! Graphical class managing the loading processes
/*!
 *  Class displaying a loading bar in a dialog while others processes are loaded.
 *  This class must be keep as light as possible, heavy processes must be in their own class.
 */
class Loader : public QDialog
{
    Q_OBJECT

public:
    //! Constructor
    /*!
     *  Initialize the class.
     *  Display ui
     *  Start loading processes
     *  \param parent the parent ClientApplication used to post events
     */
    Loader(ClientApplication *parent);
    //! Surcharge of the method event
    /*!
     *  When receiving a StartEvent, it indicate that a processe has finish his loading, so the loading bar is updated
     *  \param event the event recevied
     *  \return the accept status of the event
     */
    bool event(QEvent *event);
    //! login window
    QWidget *ld;

private:
    //! The graphical ui used
    Ui::Window ui;
    //! A counter of the number of processes
    int processes;
    //! A counter of the number of finished proccess
    int processesComplete;
    //! A pointer to its parent ClientApplication
    ClientApplication *parent;

    //! Method for start the loading of the plugins
    /*!
     *  Send an StartEvent to the PluginManager
     */
    void    loadPlugins();

    //! Method for start the loading of the network
    /*!
     *  Send an StartEvent to the NetworkManager
     */
    void    loadNetwork();
    //! Method for start the loading of the configuration
    void    loadConfig();
    //! Method for start the loading of the config
    /*!
     *  Send an StartEvent to the ConfigManager
     */
};

#endif // LOADER_H
