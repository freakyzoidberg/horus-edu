#include    "ClientApplication.h"

#include	"MetaManager.h"
#include    "../Common/Defines.h"
#include    "Loader.h"
#include    "ConfigManager.h"
#include    "ClientEvents.h"
#include    "LoginDialog.h"
#include    "NotificationClient.h"
#include    <QtDebug>

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
	MetaManager *mManager;
	NotificationClient *notification;
	Loader *loader;

    this->setOrganizationName(ORGANIZATION_NAME);
    this->setOrganizationDomain(ORGANIZATION_DOMAIN);
    this->setApplicationName(CLIENT_NAME);
    this->setApplicationVersion(CLIENT_VERSION);
    this->setApplicationVersion(CLIENT_VERSION);//pour git
	mManager = MetaManager::getInstance();
	mManager->addManager("NetworkManager", true);
	mManager->addManager("ConfigManager", true);
	mManager->addManager("PluginManager", false);
    notification = new NotificationClient();
	foreach (AbstractManager *manager, mManager->managers())
		connect(manager, SIGNAL(notified), notification, SLOT(notify));
    loader = new Loader(this);
    loader->show();
    //this->loader = new Loader(this);
    //this->loader->show();
}

ClientApplication::~ClientApplication()
{
}

bool    ClientApplication::event(QEvent *event)
{
    if (event->type() >= QEvent::User && event->type() <= QEvent::MaxUser)
        return (false);
    return (QApplication::event(event));
}

void    ClientApplication::preExit()
{
    //ThreadPlugin    *pmanager;
    //ThreadNetwork   *nmanager;
    //ConfigManager   *cmanager;

    //pmanager = this->findChild<ThreadPlugin*>();
    //nmanager = this->findChild<ThreadNetwork *>();
    //cmanager = this->findChild<ConfigManager *>();
    //QApplication::postEvent(nmanager, new QEvent(ClientEvents::StopEvent));
    //QApplication::postEvent(pmanager, new QEvent(ClientEvents::StopEvent));
    //QApplication::postEvent(cmanager, new QEvent(ClientEvents::StopEvent));
}
