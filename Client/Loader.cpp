#include "Loader.h"
#include "NetworkManager.cpp"
#include "PluginManager.cpp"
#include "ClientEvents.h"

Loader::Loader(ClientApplication *parent) : QDialog::QDialog()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->ui.LoadingBar->setValue(0);
    this->processes = 0;
    this->processesComplete = 0;
    this->loadNetwork();
    this->loadPlugins();
}

void    Loader::loadNetwork()
{
    //NetworkManager *networkManager;

    ++(this->processes);
    //networkManager = parent->findChild<NetworkManager *>();
    QApplication::postEvent(NetworkManager::getInstance(this->parent), new QEvent(ClientEvents::StartEvent));

}

void    Loader::loadPlugins()
{
    PluginManager  *pluginManager;

    ++(this->processes);
    pluginManager = parent->findChild<PluginManager *>();
    QApplication::postEvent(pluginManager, new QEvent(ClientEvents::StartEvent));
}

bool    Loader::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        event->accept();
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        //if (processes == processesComplete)
        if (processes == processesComplete + 1) // waiting for NetworkManager to send events...
        {

            this->hide();
            parent->mainWindow->show();
        }
        return (true);
    }
    return (QDialog::event(event));
}
