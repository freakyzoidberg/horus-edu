#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog();

private slots:
//	void			networkStatusChange(...);
//	void			pluginsLoaded();
//	void			dataPluginUpToDate(DataPlugin*);
private:
	QProgressBar*	_loadBar;
	QLabel*			_status;
};

#endif // LOGINDIALOG_H
