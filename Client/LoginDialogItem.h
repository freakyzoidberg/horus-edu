#ifndef LOGINDIALOGITEM_H
#define LOGINDIALOGITEM_H

#include <QFrame>
#include <QKeyEvent>
#include <QLineEdit>
#include <QGridLayout>
class	  LoginDialog;
#include "UserCache.h"
#include "NetworkManager.h"

class LoginDialogItem : public QFrame
{
	Q_OBJECT
public:
	LoginDialogItem(UserCache* cache, LoginDialog* dialog);

private:
	QLineEdit*		_login;
	QLineEdit*		_password;
	QGridLayout*	_layout;
	UserCache*		_cache;
	LoginDialog*	_dialog;

private slots:
	void login();
	void mousePressEvent(QMouseEvent*);
	void keyPressEvent (QKeyEvent *event);
	void cacheLoaded();
	void networkStatusChanged(NetworkManager::Status);
};

#endif // LOGINDIALOGITEM_H
