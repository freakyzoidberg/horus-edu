/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "LoginDialog.h"
#include "LoginDialogItem.h"
#include "PluginManagerClient.h"
#include "CacheManager.h"
#include "MainWindow.h"

LoginDialog::LoginDialog()
{
	setMinimumSize(300, 200);
	setWindowTitle(tr("Please Login"));
	setWindowIcon(QIcon(":/Pictures/2010_LOGO_horus_2_trans.png"));
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
	plug->setCurrentUser(0);
	connect(plug, SIGNAL(loadProgressChange(int)), loadBar, SLOT(setValue(int)));
	QMetaObject::invokeMethod(plug, "loadPlugins", Qt::QueuedConnection);

        setStyleSheet("LoginDialogItem:hover { background-color: rgba(0, 0, 0, 16); }");

	show();
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

void LoginDialog::accept()
{
	delete this;
	MainWindow::instance()->open();
}

#include <QCoreApplication>
void LoginDialog::closeEvent(QCloseEvent *)
{
	QCoreApplication::instance()->exit(0);
}
