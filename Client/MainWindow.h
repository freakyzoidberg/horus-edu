#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "ClientApplication.h"

//! Graphical class of the MainWindow
/*!
 *  Class containing the menus and the others widgets displayed.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor
    /*!
        Initialize UI, create actions and menus
        \param parent The parent
     */
    MainWindow(ClientApplication *parent);

private slots:
    //! Display a dialog for editing the settings
    void editSettings();

private:
    //! Create actions used in menus
    void createActions();
    //! Create menus of the window
    void createMenus();

    //! The graphical ui used for the MainWindow
    Ui::MainWindow ui;
    //! A pointer to its parent
    ClientApplication *parent;
    //! The menu regrouping the mains actions of the Client
    QMenu   *fileMenu;
    //! The menu regrouping parameters and settings
    QMenu   *editMenu;
    // The action which exit the application
    QAction *exitAction;
    // The action which edit the settings
    QAction *settingsAction;
};

#endif // MAINWINDOW_H
