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
    if (StartEvent::registerEventType(StartEvent::type) != StartEvent::type)
        qDebug() << "Warning, bad event type on register StartEvent";
    if (StopEvent::registerEventType(StopEvent::type) != StopEvent::type)
        qDebug() << "Warning, bad event type on register StopEvent";
    new PluginManager(this);
    new NetworkManager(this);
    QCoreApplication::postEvent(this, new StartEvent);
}

ClientApplication::~ClientApplication()
{
    QApplication::postEvent(this, new StopEvent);
}

bool    ClientApplication::notify(QObject *object, QEvent *event)
{
    QList<QObject *>  children;
    bool            res;

    if (event->type() < QEvent::User || event->type() > QEvent::MaxUser)
        return (QApplication::notify(object, event));
    if (object->event(event))
        return (true);
    children= object->findChildren<QObject *>();
    res = false;
    foreach(QObject *child, children)
        res &= this->notify(child, event);
    return (res);
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

