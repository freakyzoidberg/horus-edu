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

	const QList<UserCache*>& list = CacheManager::instance()->availableCaches();
	foreach (UserCache* cache, list)
		l1->addWidget(new LoginDialogItem(cache, this), 0);

	_other = new QPushButton(tr("Other"), this);
	connect(_other, SIGNAL(pressed()), this, SLOT(otherClick()));
	l1->addWidget(_other);

	if (list.length() == 0)
		otherClick();

	exec();
}

void LoginDialog::otherClick()
{
	((LoginDialog*)(_other->parent()))->layout()->removeWidget(_other);
	delete _other;

	QFormLayout* l2 = new QFormLayout;
	((QVBoxLayout*)layout())->addLayout(l2, 1);

	_login    = new QLineEdit;
	l2->addRow("Login", _login);

	_password = new QLineEdit;
	l2->addRow("Password", _password);

	QPushButton* ok = new QPushButton(tr("Ok"));
	l2->addRow("", ok);
	connect(ok, SIGNAL(clicked()), this, SLOT(loginUser()));

	_login->setFocus();
}

void LoginDialog::loginUser()
{
	if ( ! _login || ! _password || _login->text().isEmpty() || _password->text().isEmpty())
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
		loginUser();
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

LoginDialogItem::LoginDialogItem(UserCache* cache, LoginDialog* dialog) : QPushButton(dialog)
{
	_cache = cache;

	setText(cache->login()+'\n'+cache->lastUpdate().toString());
	setIcon(QIcon(":/Pictures/user.png"));
	setIconSize(QSize(48, 48));
	connect(this, SIGNAL(clicked()), this, SLOT(clicked()));
}

void LoginDialogItem::clicked()
{
//	if (_cache->lastSessionValidity() >= QDateTime::currentDateTime())
//	{
//		layout()->addWidget(new QLineEdit());
//	}
//	else
//	{
	_cache->load();
		CommLogin  l(CommLogin::LOGIN_SESSION);
		l.login = _cache->login();
		l.sessionString = _cache->lastSession();
		QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
		((LoginDialog*)(parent()))->close();
//	}
}
