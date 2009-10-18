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
#include <QPlastiqueStyle>

#include "MetaManager.h"
#include "ClientEvents.h"
#include "CacheManager.h"

LoginDialog::LoginDialog()
{
	setMinimumSize(300, 200);

	QVBoxLayout* l1 = new QVBoxLayout(this);
	l1->setMargin(30);

	const QList<UserCache*>& list = CacheManager::instance()->availableCaches();
	foreach (UserCache* cache, list)
		l1->addWidget(new LoginDialogItem(cache, this), 0);

	l1->addWidget(new LoginDialogItem(0, this), 0);
	l1->addStretch(1);

	exec();
}

LoginDialogItem::LoginDialogItem(UserCache* cache, LoginDialog* dialog) : QFrame(dialog)
{
	_cache = cache;
	_login = 0;
	_password = 0;
	_layout = new QGridLayout(this);

	setFrameStyle(Box | Sunken);
	init();
}

void LoginDialogItem::init()
{
	QLabel* label;

	if ( ! _layout->itemAtPosition(0,0))
	{
		label = new QLabel(this);
		label->setPixmap(QPixmap::fromImage(QImage(":/Pictures/user.png")));
		label->setFixedHeight(48);
		label->setFixedWidth(48);
		_layout->addWidget(label, 0, 0, 2, 1);
	}

	if (_cache)
	{
		label = new QLabel(_cache->login(), this);
		QFont font = label->font();
		font.setBold(true);
		label->setFont(font);
		_layout->addWidget(label, 0, 1, 1, 2);

		label = new QLabel("Session:", this);
		_layout->addWidget(label, 1, 1);
		if (_cache->lastSessionValidity() < QDateTime::currentDateTime())
		{
			label = new QLabel("Expired", this);
			_layout->addWidget(label, 1, 2);
		}
		else
		{
			label = new QLabel(_cache->lastSessionValidity().toString(), this);
			_layout->addWidget(label, 1, 2);
		}
	}
	else
	{
		label = new QLabel("Add a user", this);
		_layout->addWidget(label, 0, 1);
	}

//	_layout->setColumnMinimumWidth(0, 48);
}

void LoginDialogItem::mousePressEvent(QMouseEvent*)
{
	if (_cache)
	{
		if (_cache->lastSessionValidity() >= QDateTime::currentDateTime())
			loginSession();

		else if (_password)
			loginPassword(_cache->login(), _password->text());

		else
		{
			((QLabel*)(_layout->itemAtPosition(1, 1)->widget()))->setText("Password:");

			delete _layout->itemAtPosition(1, 2);
			_layout->addWidget((_password = new QLineEdit), 1, 2);
			_password->setFocus();
		}
	}
	else
	{
		if (_login && _password)
			loginPassword(_login->text(), _password->text());

		else
		{
			((QLabel*)(_layout->itemAtPosition(0, 1)->widget()))->setText("Login:");
			_layout->addWidget(new QLabel("Password:", this), 1, 1);
			_layout->addWidget((_login = new QLineEdit), 0, 2);
			_layout->addWidget((_password = new QLineEdit), 1, 2);
			_login->setFocus();
		}
	}
}

void LoginDialogItem::mouseReleaseEvent(QMouseEvent*)
{
}

void LoginDialogItem::keyPressEvent(QKeyEvent *event)
{
	if (event->key() != Qt::Key_Return)
		return;

	if (_cache && _password)
		loginPassword(_cache->login(), _password->text());

	if (_login && _password)
		loginPassword(_login->text(), _password->text());
}

void LoginDialogItem::loginSession()
{
	_cache->load();
	CommLogin  l(CommLogin::LOGIN_SESSION);
	l.login = _cache->login();
	l.sessionString = _cache->lastSession();
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
	((LoginDialog*)(parent()))->close();
}

void LoginDialogItem::loginPassword(const QString& login, const QString& pass)
{
	if (login.isEmpty() || pass.isEmpty())
		return;

	if (_cache)
		_cache->load();
	CommLogin  l(CommLogin::LOGIN_PASSWORD);
	l.login = login;
	l.password = QCryptographicHash::hash(pass.toAscii(), QCryptographicHash::Sha1);
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
	((LoginDialog*)(parent()))->close();
}
