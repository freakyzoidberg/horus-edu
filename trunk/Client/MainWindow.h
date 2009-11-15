#ifndef		MAINWINDOW_H
# define	MAINWINDOW_H

# include	<QMainWindow>
# include       <QTabWidget>
# include	"ui_MainWindow.h"

# include	"DisplayablePlugin.h"

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
	MainWindow();

private slots:
	//! Overload of the event method
	/*!
	 *  Call preExit from the QApplication when receive a CloseEvent
	 *  \param event the event received
	 *  \return the accept status of the event
	 */
	void closeEvent(QCloseEvent *event);
	//! Display a dialog for editing the settings
    void editSettings();
    //! Destroy the session and exit
    void logout();

private:
    //! Create actions used in menus
    void createActions();
    //! Create menus of the window
    void createMenus();
    //! Create tabbed menus in central widget
    void createCentralWidget();
	//! comparative function for sort displayable plugins
	static bool lessThan(DisplayablePlugin *a, DisplayablePlugin *b);
    //! The graphical ui used for the MainWindow
    Ui::MainWindow ui;
    //! The menu regrouping the mains actions of the Client
    QMenu   *fileMenu;
    //! The menu regrouping parameters and settings
    QMenu   *editMenu;
    // The action which exit the application
    QAction *exitAction;
    // The action which edit the settings
    QAction *settingsAction;
    // The action which destroy the session
    QAction *logoutAction;
    // Central widget
    QTabWidget *tabMenu;
};

#endif // MAINWINDOW_H
