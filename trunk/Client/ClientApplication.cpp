#include    "ClientApplication.h"

#include	<QMetaType>

#include    "../Common/Defines.h"

#include	"MetaManager.h"
#include    "NotificationClient.h"
#include	"LocalSettings.h"
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
	LocalSettings::createConfig();
	mManager = MetaManager::getInstance();
	mManager->addManager("NetworkManager", true);
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
	// TODO : exit all threads
}
