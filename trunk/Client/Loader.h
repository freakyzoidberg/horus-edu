#ifndef LOADER_H
#define LOADER_H

#include <QDialog>

#include "ui_Loader.h"

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
     */
    Loader();
    //! Surcharge of the method event
    /*!
     *  When receiving a StartEvent, it indicate that a processe has finish his loading, so the loading bar is updated
     *  \param event the event recevied
     *  \return the accept status of the event
     */
    bool event(QEvent *event);

private:
    //! The graphical ui used
    Ui::Window ui;
    //! A counter of the number of processes
    int processes;
    //! A counter of the number of finished proccess
    int processesComplete;
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
    /*!
     *  Send an StartEvent to the ConfigManager
     */
    void    loadSettings();
};

#endif // LOADER_H
