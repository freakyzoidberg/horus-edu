/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
