#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QObject>
#include <QKeyEvent>
#include <QLineEdit>
#include <QGridLayout>
#include <QFrame>
#include "../Common/CommLogin.h"
#include "UserCache.h"

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QDialog
{
//    Q_OBJECT

public:
				LoginDialog();

//private:
//    //! Method to send an event to networkManager
//    void        connectMethod();
//private slots:
//	void		otherClick();
//	void		loginUser();
//	void		keyPressEvent (QKeyEvent *event);
//private:
//	QPushButton* _other;
//	QLineEdit*	_login;
//	QLineEdit*	_password;
};

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
#endif // LOGINDIALOG_H
