#include "Loader.h"
#include "NetworkManager.cpp"
#include "PluginManager.cpp"

Loader::Loader(QObject *parent) : QDialog::QDialog()
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
    NetworkManager *networkManager;

    ++(this->processes);
    networkManager = parent->findChild<NetworkManager *>();
    QApplication::postEvent(networkManager, new StartEvent);
}

void    Loader::loadPlugins()
{
    PluginManager  *pluginManager;

    ++(this->processes);
    pluginManager = parent->findChild<PluginManager *>();
    QApplication::postEvent(pluginManager, new StartEvent);
}

bool    Loader::event(QEvent *event)
{
    if (event->type() == StartEvent::type)
    {
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        this->ui.LoadingBar->update();
    }
    return (QDialog::event(event));
}
