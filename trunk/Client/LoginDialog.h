#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QWidget>
#include "ui_LoginDialog.h"
#include "NetworkManager.h"
#include "ClientEvents.h"

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QWidget {
    Q_OBJECT
public:
    LoginDialog(QObject *parent = 0);

     //bool            event(QEvent *event);
    ~LoginDialog();

private:
    Ui::Form l_ui;

    //! LoginDialog's parent to send event to NetworkManager
    QObject *parent;

private slots:
    //! the connect button click event
    void on_connectButton_clicked();
};

#endif // LOGINDIALOG_H
