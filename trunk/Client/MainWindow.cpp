#include "MainWindow.h"
#include "SettingsDialog.h"
#include "DisplayablePlugin.h"
#include "ClientEvents.h"
#include "PluginManagerClient.h"
#include "DockMenu.h"
#include "MetaManager.h"

MainWindow::MainWindow(ClientApplication *parent) : QMainWindow()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->createActions();
    this->createMenus();
    this->addDockWidget(Qt::LeftDockWidgetArea, new DockMenu(this));
    DisplayablePlugin *mainBoard = MetaManager::getInstance()->findManager<PluginManager *>()->findPlugin<DisplayablePlugin*>("MainFrame");
    if (mainBoard)
        this->setCentralWidget(mainBoard->getWidget());
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
        this->parent->preExit();
    return (QMainWindow::event(event));
}

void    MainWindow::createActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setShortcut(tr("Ctrl+T"));
    settingsAction->setStatusTip(tr("Edit settings of Horus"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(editSettings()));
}

void    MainWindow::createMenus()
{
    this->fileMenu = this->ui.menubar->addMenu(tr("&File"));
    this->fileMenu->addAction(exitAction);
    this->editMenu = this->ui.menubar->addMenu(tr("&Edit"));
    this->editMenu->addAction(settingsAction);
}

void    MainWindow::editSettings()
{
    SettingsDialog  *dialog;

    dialog = new SettingsDialog(this);
    dialog->show();
}