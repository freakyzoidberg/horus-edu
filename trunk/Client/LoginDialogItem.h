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
	void init();
private:
	void loginSession();
	void loginPassword(const QString& login, const QString& pass);

	QLineEdit*		_login;
	QLineEdit*		_password;
	QGridLayout*	_layout;
	UserCache*		_cache;

private slots:
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void keyPressEvent (QKeyEvent *event);
};

#endif // LOGINDIALOGITEM_H
