#include "LoginDialogItem.h"
#include "LoginDialog.h"

#include <QLabel>
#include <QCryptographicHash>
#include "PluginManagerClient.h"

LoginDialogItem::LoginDialogItem(UserCache* cache, LoginDialog* dialog) : QFrame(dialog)
{
	_cache = cache;
	_dialog = dialog;
	_login = 0;
	_password = 0;
	_layout = new QGridLayout(this);

	setFrameStyle(Box | Sunken);

	QLabel* label;

	//picture
	label = new QLabel(this);
	label->setPixmap(QPixmap::fromImage(QImage(":/Pictures/user.png")));
	label->setFixedHeight(48);
	label->setFixedWidth(48);
	_layout->addWidget(label, 0, 0, 2, 1);

	//if existing user
	if (_cache)
	{
		label = new QLabel(_cache->login(), this);
		QFont font = label->font();
		font.setBold(true);
		label->setFont(font);
		_layout->addWidget(label, 0, 1, 1, 2);

		label = new QLabel(tr("Session:"), this);
		_layout->addWidget(label, 1, 1);
		if (_cache->lastSessionValidity() < QDateTime::currentDateTime())
		{
			label = new QLabel(tr("Expired"), this);
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
		label = new QLabel(tr("Sign in with a new user"), this);
		_layout->addWidget(label, 0, 1);
	}
}

void LoginDialogItem::mousePressEvent(QMouseEvent* event)
{
	event->accept();

	if (_cache)
	{
		if (_cache->lastSessionValidity() >= QDateTime::currentDateTime())
			login();
		else if ( ! _password)
		{
			((QLabel*)(_layout->itemAtPosition(1, 1)->widget()))->setText("Password:");
			QLayoutItem* item = _layout->itemAtPosition(1, 2);
			_layout->removeItem(item);
			delete item;
			_layout->addWidget((_password = new QLineEdit), 1, 2);
			_password->setEchoMode(QLineEdit::Password);
			_password->setFocus();
		}
		else if ( ! _password->text().isEmpty())
				login();
	}
	else
	{
		NetworkManager* net = NetworkManager::instance();
		if (net->status() != NetworkManager::ESTABLISHED)
		{
			((QLabel*)(_layout->itemAtPosition(0, 1)->widget()))->setText("You need to be connected.");
			if (net->status() == NetworkManager::DISCONNECTED)
				QMetaObject::invokeMethod(net, "tryToConnect", Qt::QueuedConnection);
		}
		else if ( ! _login)
		{
			((QLabel*)(_layout->itemAtPosition(0, 1)->widget()))->setText(tr("Login")+':');
			_layout->addWidget(new QLabel(tr("Password")+':', this), 1, 1);
			_layout->addWidget((_login = new QLineEdit), 0, 2);
			_layout->addWidget((_password = new QLineEdit), 1, 2);
			_password->setEchoMode(QLineEdit::Password);
			_login->setFocus();
		}
		else if ( ! _login->text().isEmpty() && ! _password->text().isEmpty())
			login();
	}
}

void LoginDialogItem::keyPressEvent(QKeyEvent *event)
{
	if (event->key() != Qt::Key_Return)
		return;

	if ((_cache || _login) && _password)
	{
		event->accept();
		login();
	}
}

void LoginDialogItem::login()
{
	PluginManagerClient* pluginManager = PluginManagerClient::instance();
	if ( ! pluginManager->isLoaded())
	{
		connect(pluginManager, SIGNAL(loaded()), this, SLOT(login()));
		return;
	}

	if (_cache)
	{
		connect(_cache, SIGNAL(loadProgressChange(int)), _dialog->loadBar, SLOT(setValue(int)));
		connect(_cache, SIGNAL(loaded()), this, SLOT(cacheLoaded()));
		QMetaObject::invokeMethod(_cache, "load", Qt::QueuedConnection);
	}
	else
		cacheLoaded();
}

void LoginDialogItem::cacheLoaded()
{
	NetworkManager* net = NetworkManager::instance();

	//case no network
	if (net->status() == NetworkManager::ESTABLISHED)
	{
		connect(net, SIGNAL(updateProgressChange(int)), _dialog->loadBar, SLOT(setValue(int)));
		connect(net, SIGNAL(statusChange(NetworkManager::Status)), this, SLOT(networkStatusChanged(NetworkManager::Status)));

		if ( ! _cache)
			QMetaObject::invokeMethod(net, "loginPassword", Qt::QueuedConnection, Q_ARG(const QString, _login->text()), Q_ARG(const QString, _password->text()));

		else if ( ! _password)
			QMetaObject::invokeMethod(net, "loginSession", Qt::QueuedConnection, Q_ARG(const QString, _cache->login()), Q_ARG(const QByteArray, _cache->lastSession()));

		else
			QMetaObject::invokeMethod(net, "loginPassword", Qt::QueuedConnection, Q_ARG(const QString, _cache->login()), Q_ARG(const QString, _password->text()));

	}
	else if (net->status() == NetworkManager::DISCONNECTED)
		_dialog->accept();
}

void LoginDialogItem::networkStatusChanged(NetworkManager::Status status)
{
	disconnect(this, SLOT(networkStatusChanged(NetworkManager::Status)));
	disconnect(_dialog->loadBar, SLOT(setValue(int)));
	_dialog->loadBar->setValue(100);
	if (status == NetworkManager::ESTABLISHED)
	{
		if ( ! _password)
		{
			((QLabel*)(_layout->itemAtPosition(1, 1)->widget()))->setText("Password:");
			QLayoutItem* item = _layout->itemAtPosition(1, 2);
			_layout->removeItem(item);
			delete item;
			_layout->addWidget((_password = new QLineEdit), 1, 2);
			_password->setFocus();
			_password->setEchoMode(QLineEdit::Password);
		}
		else
		{
			_password->setText("");
			_password->setFocus();
		}
	}
	else if (status == NetworkManager::LOGGED_IN)
		_dialog->accept();
}
