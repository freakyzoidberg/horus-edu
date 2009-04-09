#include    "ClientApplication.h"
#include    "../Common/Defines.h"
#include    "NetworkManager.h"
#include    "PluginManager.h"
#include    "StartEvent.h"
#include    "StopEvent.h"
#include    <QtDebug>

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(CLIENT_NAME);
    QCoreApplication::setApplicationVersion(CLIENT_VERSION);
    StartEvent::registerEventType(StartEvent::type);
    StopEvent::registerEventType(StopEvent::type);
    new PluginManager(this);
    new NetworkManager(this);
    QApplication::postEvent(this, new StartEvent);
}

ClientApplication::~ClientApplication()
{
    QApplication::postEvent(this, new StopEvent);
}

void    ClientApplication::reloadPlugins()
{
    PluginManager   *manager;

    manager = this->findChild<PluginManager *>();
    QApplication::postEvent(manager, new StopEvent);
    QApplication::postEvent(manager, new StartEvent);
}

void    ClientApplication::restartNetwork()
{
    NetworkManager   *manager;

    manager = this->findChild<NetworkManager *>();
    QApplication::postEvent(manager, new StopEvent);
    QApplication::postEvent(manager, new StartEvent);
}

