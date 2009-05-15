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

    ~LoginDialog();

private:
    //! The graphical ui used
    Ui::Form l_ui;

    //! LoginDialog's parent to send event to NetworkManager
    QObject *parent;

private slots:
    //! callback of the connect button, it send an event to NetworkManager
    void on_connectButton_clicked();
};

#endif // LOGINDIALOG_H
