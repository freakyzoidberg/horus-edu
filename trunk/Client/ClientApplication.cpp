#include    "ClientApplication.h"

#include	<QMetaType>

#include    "../Common/Defines.h"

#include	"MetaManager.h"
#include    "NotificationClient.h"
#include    "Loader.h"
#include	"MainWindow.h"

void QtNotify(QtMsgType type, const char *message);

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
	MetaManager *mManager;
	NotificationClient *notification;
	Loader *loader;

	qRegisterMetaType<Notification::type>();
	qInstallMsgHandler(QtNotify);
    this->setOrganizationName(ORGANIZATION_NAME);
    this->setOrganizationDomain(ORGANIZATION_DOMAIN);
    this->setApplicationName(CLIENT_NAME);
    this->setApplicationVersion(CLIENT_VERSION);
    this->setApplicationVersion(CLIENT_VERSION);//pour git
	mManager = MetaManager::getInstance();
	mManager->addManager("NetworkManager", true);
	//mManager->addManager("ConfigManager", true);
	mManager->addManager("PluginManager", false);
	notification = NotificationClient::getInstance();
	foreach (AbstractManager *manager, mManager->managers())
		connect(manager, SIGNAL(notified(Notification::type, QString)), notification, SLOT(notify(Notification::type, QString)));
    loader = new Loader();
	connect(loader, SIGNAL(accepted()), this, SLOT(loadingComplete()));
	connect(loader, SIGNAL(rejected()), this, SLOT(preExit()));
    loader->show();
}

void	ClientApplication::loadingComplete()
{
	MainWindow *window;

	window = new MainWindow(this);
	window->show();
}

ClientApplication::~ClientApplication()
{
	this->preExit();
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
