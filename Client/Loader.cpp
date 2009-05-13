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
    QSettings settings;


    if (event->type() == StartEvent::type)
    {
        event->accept();
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        //if (processes == processesComplete)
        if (processes == processesComplete + 1) // waiting for NetworkManager to send events...
        {
            settings.beginGroup("SESSIONS");
            if (settings.value("sessionString", "") != "")
            {
                if (settings.value("sessionEnd", 0).toUInt() > (QDateTime::currentDateTime().toTime_t() + 60))
                {
                    NetworkManager::getInstance(this->parent)->login(settings.value("sessionLogin", "").toString(), settings.value("sessionString", "").toString(), 2);
                }
                else
                {
                    //this->hide();
                    //parent->ld->show();
                }
            }
            this->hide();
            parent->mainWindow->show();
        }
        return (true);
    }
    return (QDialog::event(event));
}
