#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include "NetworkManager.h"

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog();

private slots:
	void			networkStatusChange(NetworkManager::Status);

public:
	QProgressBar*	loadBar;
private:
	QLabel*			_connexionStatus;
};

#endif // LOGINDIALOG_H
