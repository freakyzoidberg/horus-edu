#include "LoginDialog.h"
#include "LoginDialogItem.h"

#include "CacheManager.h"

LoginDialog::LoginDialog()
{
	setMinimumSize(300, 200);

	QVBoxLayout* l1 = new QVBoxLayout(this);
	//l1->setMargin(16);

	const QList<UserCache*>& list = CacheManager::instance()->availableCaches();
	foreach (UserCache* cache, list)
		l1->addWidget(new LoginDialogItem(cache, this), 0);

	l1->addWidget(new LoginDialogItem(0, this), 0);
	l1->addStretch(1);

	_status = new QLabel("futur status info");
	_status->setAlignment(Qt::AlignCenter);
	_status->setFixedHeight(16);
	l1->addWidget(_status, 0);

	_loadBar = new QProgressBar;
	_loadBar->setRange(0, 0);
	_loadBar->setValue(0);
	_loadBar->setFixedHeight(16);
	l1->addWidget(_loadBar, 0);

	exec();
}

