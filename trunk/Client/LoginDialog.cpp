#include "LoginDialog.h"
#include "LoginDialogItem.h"
#include "PluginManagerClient.h"
#include "CacheManager.h"

LoginDialog::LoginDialog()
{
	setMinimumSize(300, 200);
	NetworkManager* net = NetworkManager::instance();
	QVBoxLayout* l1 = new QVBoxLayout(this);
	l1->setContentsMargins(10,10,10,10);

	const QList<UserCache*>& list = CacheManager::instance()->availableCaches();
	foreach (UserCache* cache, list)
		l1->addWidget(new LoginDialogItem(cache, this), 0);

	l1->addWidget(new LoginDialogItem(0, this), 0);
	l1->addStretch(1);

	QHBoxLayout* l2 = new QHBoxLayout;
	l2->setSpacing(0);

	_connexionStatus = new QLabel;
	networkStatusChange(NetworkManager::CONNECTED);
	l2->addWidget(_connexionStatus, 0);

	loadBar = new QProgressBar;
	loadBar->setFixedHeight(6);
	loadBar->setTextVisible(false);
	loadBar->setRange(0, 100);
	loadBar->setValue(0);

	l2->addWidget(loadBar, 1, Qt::AlignBottom);

	l1->addLayout(l2, 0);

	qRegisterMetaType<NetworkManager::Status>("NetworkManager::Status");
	connect(net, SIGNAL(statusChange(NetworkManager::Status)), this, SLOT(networkStatusChange(NetworkManager::Status)));
	QMetaObject::invokeMethod(net, "tryToConnect", Qt::QueuedConnection);

	PluginManagerClient* plug = PluginManagerClient::instance();
	connect(plug, SIGNAL(loadProgressChange(int)), loadBar, SLOT(setValue(int)));
	QMetaObject::invokeMethod(plug, "loadPlugins", Qt::QueuedConnection);

	setStyleSheet("LoginDialogItem:hover { background-color: rgba(0, 0, 0, 32); }");

	exec();
}

void LoginDialog::networkStatusChange(NetworkManager::Status status)
{
	if (status == NetworkManager::DISCONNECTED)
		_connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/disconnected.png")));
	else if (status == NetworkManager::CONNECTED)
		_connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/connecting.png")));
	else
		_connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/connected.png")));
}
