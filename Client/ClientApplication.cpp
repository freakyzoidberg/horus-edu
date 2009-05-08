#include    "ClientApplication.h"
#include    "../Common/Defines.h"
#include    "Loader.h"
#include    "NetworkManager.h"
#include    "PluginManager.h"
#include    "StartEvent.h"
#include    "StopEvent.h"
#include    <QtDebug>

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    this->setOrganizationName(ORGANIZATION_NAME);
    this->setOrganizationDomain(ORGANIZATION_DOMAIN);
    this->setApplicationName(CLIENT_NAME);
    this->setApplicationVersion(CLIENT_VERSION);
    if (StartEvent::registerEventType(StartEvent::type) != StartEvent::type)
        qDebug() << "Warning, bad event type on register StartEvent";
    if (StopEvent::registerEventType(StopEvent::type) != StopEvent::type)
        qDebug() << "Warning, bad event type on register StopEvent";
    new NetworkManager(this);
    new PluginManager(this);
    this->loader = new Loader(this);
    this->loader->show();
}

ClientApplication::~ClientApplication()
{
    QApplication::postEvent(this, new StopEvent);
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

