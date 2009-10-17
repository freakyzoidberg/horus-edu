#include "LoginDialog.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDir>
#include <QCryptographicHash>
#include <QDebug>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

#include "MetaManager.h"
#include "ClientEvents.h"

#include "CacheManager.h"

LoginDialog::LoginDialog()
{
	_login = 0;
	_password = 0;

	setMinimumSize(300, 200);

	QVBoxLayout* l1 = new QVBoxLayout(this);
	l1->setMargin(30);

	//CacheManager::instance()->userCache("git");

	foreach (UserCache* cache, CacheManager::instance()->availableCaches())
	{
		QPushButton* button = new QPushButton(cache->login(), this);
		connect(button, SIGNAL(pressed()), this, SLOT(userSelected()));
		l1->addWidget(button, 0);
	}

	QPushButton* button = new QPushButton(tr("Other"), this);
	connect(button, SIGNAL(pressed()), this, SLOT(otherUser()));
	l1->addWidget(button);

//	QCheckBox* remember = new QCheckBox(tr("Remember my choice"), this);
//	l1->addWidget(remember);

	exec();
}

void LoginDialog::otherUser()
{
	qDebug() << sender();
	QPushButton* other = ((QPushButton*)sender());
	((LoginDialog*)(other->parent()))->layout()->removeWidget(other);
	delete other;
//	((LoginDialog*)(other->parent()))->layout()->update();

	QFormLayout* l2 = new QFormLayout;
	((QVBoxLayout*)layout())->addLayout(l2, 1);

	_login    = new QLineEdit;
	l2->addRow("Login", _login);

	_password = new QLineEdit;
	l2->addRow("Password", _password);

	QPushButton* ok = new QPushButton(tr("Ok"));
	l2->addRow("", ok);
	connect(ok, SIGNAL(clicked()), this, SLOT(loginNewUser()));

	_login->setFocus();
}

void LoginDialog::userSelected()
{
	CommLogin  l(CommLogin::LOGIN_SESSION);
	l.login = ((QPushButton*)sender())->text();
	l.sessionString = CacheManager::instance()->userCache(l.login)->lastSession();
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
	close();
}

void LoginDialog::loginNewUser()
{
	if ( ! _login || ! _password)
		return;

	CommLogin  l(CommLogin::LOGIN_PASSWORD);
	l.login = _login->text();
	l.password = QCryptographicHash::hash(_password->text().toAscii(), QCryptographicHash::Sha1);
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
	close();
}

//void    LoginDialog::closeEvent()
//{
//	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new QEvent(ClientEvents::OfflineModeEvent));
//}

void    LoginDialog::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return)
		loginNewUser();
}

//void LoginDialog::on_connectButton_clicked()
//{
//    connectMethod();
//}

//void    LoginDialog::connectMethod()
//{
//    if (l_ui.loginE->text() != "" || l_ui.passE->text() != "")
//    {
//        QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
//        settings.beginGroup("SESSIONS");
//        settings.setValue("sessionString", "");
//        settings.setValue("sessionLogin", l_ui.loginE->text());
//        settings.setValue("sessionTime", "");
//        settings.setValue("sessionEnd", "");
//        CommLogin  l(CommLogin::LOGIN_PASSWORD);
//        l.login = l_ui.loginE->text();
//        l.password = QCryptographicHash::hash(l_ui.passE->text().toUtf8(), QCryptographicHash::Sha1);
//        QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
//        settings.endGroup();
//		delete this;
//    }
//}
