#include "Loader.h"
#include "ConfigManager.h"
#include "ThreadNetwork.h"
#include "PluginManager.h"
#include "ClientEvents.h"
#include "LoginDialog.h"
#include "MainWindow.h"

Loader::Loader(ClientApplication *parent) : QDialog::QDialog()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->ui.LoadingBar->setValue(0);
    this->processes = 0;
    this->processesComplete = 0;
    this->loadNetwork();
    this->loadConfig();
    this->loadPlugins();
    ld = new LoginDialog(this->parent);
}

void    Loader::closeEvent(QCloseEvent *event)
{
    this->parent->preExit();
}

void    Loader::loadNetwork()
{
    //NetworkManager *networkManager;
    ++(this->processes);
    //networkManager = parent->findChild<NetworkManager *>();
    QApplication::postEvent(ThreadNetwork::getInstance(this->parent), new QEvent(ClientEvents::StartEvent));
}

void    Loader::loadPlugins()
{
    PluginManager  *pluginManager;

    ++(this->processes);
    pluginManager = parent->findChild<PluginManager *>();
    QApplication::postEvent(pluginManager, new QEvent(ClientEvents::StartEvent));
}

void    Loader::loadConfig()
{
    ConfigManager   *configManager;

    ++(this->processes);
    configManager = parent->findChild<ConfigManager *>();
    QApplication::postEvent(configManager, new QEvent(ClientEvents::StartEvent));
}

bool    Loader::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        event->accept();
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (processes == processesComplete)
        {
            this->hide();
            parent->mainWindow = new MainWindow(this->parent);
            parent->mainWindow->show();
        }
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        event->accept();
        --(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (0 == processesComplete)
            ClientApplication::exit(0);
        return (true);
    }
    else if (event->type() == ClientEvents::ShowLoginEvent)
    {
        ld->show();
    }
    else if (event->type() == ClientEvents::HideLoginEvent)
    {

        if (ld != NULL)
        {
            ld->hide();
            delete ld;
        }
    }
    return (QDialog::event(event));
}
