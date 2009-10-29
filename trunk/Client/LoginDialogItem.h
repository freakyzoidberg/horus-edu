#ifndef LOGINDIALOGITEM_H
#define LOGINDIALOGITEM_H

#include <QFrame>
#include <QKeyEvent>
#include <QLineEdit>
#include <QGridLayout>
class	  LoginDialog;
#include "UserCache.h"

class LoginDialogItem : public QFrame
{
	Q_OBJECT
public:
	LoginDialogItem(UserCache* cache, LoginDialog* dialog);

private:
	void login();

	QLineEdit*		_login;
	QLineEdit*		_password;
	QGridLayout*	_layout;
	UserCache*		_cache;
	LoginDialog*	_dialog;

private slots:
	void mousePressEvent(QMouseEvent*);
	void keyPressEvent (QKeyEvent *event);
	void cacheLoaded();
};

#endif // LOGINDIALOGITEM_H
