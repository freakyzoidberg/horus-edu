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
#include "MainWindow.h"

#include <QDir>
#include <QPushButton>
#include <QLabel>

#include "CacheManager.h"
#include "SettingsDialog.h"
#include "DisplayablePlugin.h"
#include "PluginManagerClient.h"
#include "LoginDialog.h"

MainWindow* MainWindow::instance()
{
	static MainWindow* window = new MainWindow;
	return window;
}

void MainWindow::open()
{
	createCentralWidget();
	show();
}

void MainWindow::close()
{
	delete centralWidget();
	hide();
	new LoginDialog;
}

MainWindow::MainWindow()
{
	ui.setupUi(this);
        //createActions();
        //createMenus();
	ui.menubar->setVisible(false);
}

void MainWindow::closeEvent(QCloseEvent*)
{
	CacheManager::instance()->save();
	QApplication::instance()->exit();
}

void    MainWindow::createActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    settingsAction = new QAction(QIcon(":/Pictures/configure.png"), tr("Se&ttings"), this);
    settingsAction->setShortcut(tr("Ctrl+T"));
    settingsAction->setStatusTip(tr("Edit settings of Horus"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(editSettings()));

	logoutAction = new QAction(tr("Log &Out"), this);
    logoutAction->setShortcut(tr("Ctrl+D"));
    logoutAction->setStatusTip(tr("Destroy the session"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(logout()));
}

void    MainWindow::createMenus()
{
    this->fileMenu = this->ui.menubar->addMenu(tr("&File"));
    this->editMenu = this->ui.menubar->addMenu(tr("&Edit"));
	// Following is FAKE
	QAction *separator;
	QAction *fake;
	fake = new QAction(QIcon(":/Pictures/filenew-16.png"), tr("New..."), this);
	fake->setShortcut(tr("Ctrl+N"));
    this->fileMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/prefix-add.png"), tr("Load..."), this);
	fake->setShortcut(tr("Ctrl+L"));
    this->fileMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/fileopen-16.png"), tr("Save"), this);
    this->fileMenu->addAction(fake);
	fake->setShortcut(tr("Ctrl+S"));
	fake = new QAction(QIcon(":/Pictures/fileopen-16.png"), tr("Save As..."), this);
    this->fileMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/fileopen-16.png"), tr("Save All"), this);
    this->fileMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->fileMenu->addAction(separator);
	fake = new QAction(tr("Close"), this);
	fake->setShortcut(tr("Ctrl+W"));
    this->fileMenu->addAction(fake);
	fake = new QAction(tr("Close All"), this);
    this->fileMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->fileMenu->addAction(separator);
	fake = new QAction(tr("Page Setup..."), this);
	fake->setShortcut(tr("Ctrl+E"));
    this->fileMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/print.png"), tr("Print..."), this);
	fake->setShortcut(tr("Ctrl+P"));
    this->fileMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/print.png"), tr("Print Preview..."), this);
    this->fileMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->fileMenu->addAction(separator);
	fake = new QAction(QIcon(":/Pictures/undo.png"), tr("Undo"), this);
	fake->setShortcut(tr("Ctrl+U"));
	this->editMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/redo.png"), tr("Redo"), this);
	fake->setShortcut(tr("Ctrl+R"));
	this->editMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->editMenu->addAction(separator);
	fake = new QAction(QIcon(":/Pictures/editcopy.png"), tr("Cut"), this);
	fake->setShortcut(tr("Ctrl+C"));
	this->editMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/editcopy.png"), tr("Copy"), this);
	fake->setShortcut(tr("Ctrl+V"));
	this->editMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/editcopy.png"), tr("Paste"), this);
	fake->setShortcut(tr("Ctrl+X"));
	this->editMenu->addAction(fake);
	fake = new QAction(tr("Delete"), this);
	this->editMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->editMenu->addAction(separator);
	fake = new QAction(tr("Select All"), this);
	fake->setShortcut(tr("Ctrl+A"));
	this->editMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->editMenu->addAction(separator);
	fake = new QAction(QIcon(":/Pictures/find.png"), tr("Replace..."), this);
	fake->setShortcut(tr("Ctrl+F"));
	this->editMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    this->editMenu->addAction(separator);
	QMenu *viewMenu = this->ui.menubar->addMenu(tr("&View"));
	fake = new QAction(QIcon(":/Pictures/home.png"), tr("Main Board"), this);
	fake->setShortcut(tr("Alt+H"));
	viewMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/edit.png"), tr("Course"), this);
	fake->setShortcut(tr("Alt+C"));
	viewMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/book.png"), tr("Marks"), this);
	fake->setShortcut(tr("Alt+M"));
	viewMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/calendarwidget.png"), tr("Calendar"), this);
	fake->setShortcut(tr("Alt+L"));
	viewMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/configure.png"), tr("Administration"), this);
	fake->setShortcut(tr("Alt+A"));
	viewMenu->addAction(fake);
	QMenu *toolsMenu = this->ui.menubar->addMenu(tr("&Tools"));
	fake = new QAction(QIcon(":/Pictures/configure.png"), tr("Editor"), this);
	toolsMenu->addAction(fake);
	fake = new QAction(tr("Remote"), this);
	toolsMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    toolsMenu->addAction(separator);
	fake = new QAction(tr("Debugger"), this);
	fake->setShortcut(tr("Ctrl+G"));
	toolsMenu->addAction(fake);
	fake = new QAction(tr("Console"), this);
	toolsMenu->addAction(fake);
	QMenu *helpMenu = this->ui.menubar->addMenu(tr("&Help"));
	fake = new QAction(QIcon(":/Pictures/find.png"), tr("Search"), this);
	fake->setShortcut(tr("Ctrl+F1"));
	helpMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/book.png"), tr("Content"), this);
	fake->setShortcut(tr("Ctrl+F2"));
	helpMenu->addAction(fake);
	fake = new QAction(QIcon(":/Pictures/home.png"), tr("Index"), this);
	fake->setShortcut(tr("Ctrl+F3"));
	helpMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    helpMenu->addAction(separator);
	fake = new QAction(tr("?"), this);
	fake->setShortcut(tr("Ctrl+?"));
	helpMenu->addAction(fake);
	fake = new QAction(tr("Report Bug"), this);
	helpMenu->addAction(fake);
	separator = new QAction(this);
	separator->setSeparator(true);
    helpMenu->addAction(separator);
	fake = new QAction(tr("About"), this);
	helpMenu->addAction(fake);
	// Following isn't FAKE
    this->fileMenu->addAction(logoutAction);
    this->fileMenu->addAction(exitAction);
    this->editMenu->addAction(settingsAction);
}

void							MainWindow::createCentralWidget()
{
	QWidget						*currentWidget;
	QTabWidget					*subMenu;
	QList<DisplayablePlugin *>	plugins;

	tabMenu = new QTabWidget(this);
	tabMenu->setTabShape(QTabWidget::Triangular);
	tabMenu->setTabPosition(QTabWidget::West);
	setCentralWidget(tabMenu);
	plugins = PluginManagerClient::instance()->findPlugins<DisplayablePlugin*>();
	qSort(plugins.begin(), plugins.end(), MainWindow::lessThan);
	foreach (DisplayablePlugin* plugin, plugins)
		if (!plugin->getDisplayableName().isEmpty())
		{
			currentWidget = plugin->getWidget();
			if (currentWidget == NULL)
				continue;
			QWidget *host = new QWidget;
			QGridLayout *layout = new QGridLayout(host);
			layout->setMargin(0);
			layout->setSpacing(0);	
			layout->addWidget(currentWidget, 0, 0);
			currentWidget->show();
			subMenu = qobject_cast<QTabWidget *>(currentWidget);
			if (subMenu)
			{
				subMenu->setTabShape(QTabWidget::Triangular);
				subMenu->setTabPosition(QTabWidget::North);
				host->setProperty("hasSubMenu", QVariant(true));
			}
			tabMenu->addTab(host, plugin->getIcon(), plugin->getDisplayableName());
		}
}

bool							MainWindow::lessThan(DisplayablePlugin *a, DisplayablePlugin *b)
{
	return (a->getOrder() < b->getOrder());
}

void    MainWindow::editSettings()
{
    SettingsDialog  *dialog;

    dialog = new SettingsDialog(this);
    dialog->show();
}

void	MainWindow::logout()
{
	//todo: send LoginPacket::LOGOUT
	//todo: save and free the cache
	//todo: open LoginDialog
	close();
}
