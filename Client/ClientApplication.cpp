#include    "ClientApplication.h"
#include    "../Common/Defines.h"
#include    "Loader.h"
#include    "NetworkManager.h"
#include    "PluginManager.h"
#include    "ClientEvents.h"
#include    "MainWindow.h"
#include    "LoginDialog.h"
#include    <QtDebug>

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    this->setOrganizationName(ORGANIZATION_NAME);
    this->setOrganizationDomain(ORGANIZATION_DOMAIN);
    this->setApplicationName(CLIENT_NAME);
//    this->setApplicationVersion(CLIENT_VERSION);
    NetworkManager::getInstance(this);
    new PluginManager(this);
    this->loader = new Loader(this);
    this->mainWindow = new MainWindow(this);
    this->loader->show();
}

ClientApplication::~ClientApplication()
{
    //QApplication::postEvent(manager, new StopEvent);
    QApplication::postEvent(this, new QEvent(ClientEvents::StopEvent));
}

bool    ClientApplication::event(QEvent *event)
{
    if (event->type() >= QEvent::User && event->type() <= QEvent::MaxUser)
        return (false);
    return (QApplication::event(event));
}

void    ClientApplication::reloadPlugins()
{
    PluginManager   *manager;

    manager = this->findChild<PluginManager *>();
    QApplication::postEvent(this, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(this, new QEvent(ClientEvents::StartEvent));
    //QApplication::postEvent(manager, new StopEvent);
    //QApplication::postEvent(manager, new StartEvent);
}

void    ClientApplication::restartNetwork()
{
    NetworkManager   *manager;

    manager = this->findChild<NetworkManager *>();
    QApplication::postEvent(this, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(this, new QEvent(ClientEvents::StartEvent));
    //QApplication::postEvent(manager, new StopEvent);
    //QApplication::postEvent(manager, new StartEvent);
}

