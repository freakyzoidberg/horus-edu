#include "MainWindow.h"
#include "SettingsDialog.h"
#include "ClientEvents.h"

MainWindow::MainWindow(ClientApplication *parent) : QMainWindow::QMainWindow()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->createActions();
    this->createMenus();
 //   this->setCentralWidget(new MainBoard(this));
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        this->parent->preExit();
        return (true);
    }
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
