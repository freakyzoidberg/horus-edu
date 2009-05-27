#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent) : QMainWindow::QMainWindow()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->createActions();
    this->createMenus();
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

}
