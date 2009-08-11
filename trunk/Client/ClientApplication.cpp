#include    "ClientApplication.h"
#include    "../Common/Defines.h"
#include    "Loader.h"
#include    "ThreadPlugin.h"
#include    "ConfigManager.h"
#include    "ClientEvents.h"
#include    "LoginDialog.h"
#include    "ThreadNetwork.h"
#include    <QtDebug>

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    this->nC = new NotificationClient(this);
    ThreadNetwork::getInstance(this);
    this->setOrganizationName(ORGANIZATION_NAME);
    this->setOrganizationDomain(ORGANIZATION_DOMAIN);
    this->setApplicationName(CLIENT_NAME);
    this->setApplicationVersion(CLIENT_VERSION);
    //pour segfault a git
    this->setApplicationVersion(CLIENT_VERSION);
    new ConfigManager(this);
    new ThreadPlugin(this);
    this->loader = new Loader(this);
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
    ThreadPlugin* manager = this->findChild<ThreadPlugin*>();
    QApplication::postEvent(this, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(this, new QEvent(ClientEvents::StartEvent));
    QApplication::postEvent(manager, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(manager, new QEvent(ClientEvents::StartEvent));
}

void    ClientApplication::restartNetwork()
{
    NetworkManager* manager = this->findChild<NetworkManager *>();
    QApplication::postEvent(this, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(this, new QEvent(ClientEvents::StartEvent));
    QApplication::postEvent(manager, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(manager, new QEvent(ClientEvents::StartEvent));
}

void    ClientApplication::preExit()
{
    ThreadPlugin    *pmanager;
    ThreadNetwork   *nmanager;
    ConfigManager   *cmanager;

    pmanager = this->findChild<ThreadPlugin*>();
    nmanager = this->findChild<ThreadNetwork *>();
    cmanager = this->findChild<ConfigManager *>();
    QApplication::postEvent(nmanager, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(pmanager, new QEvent(ClientEvents::StopEvent));
    QApplication::postEvent(cmanager, new QEvent(ClientEvents::StopEvent));
}