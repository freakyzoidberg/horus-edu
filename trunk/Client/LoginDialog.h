#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QWidget>
#include "ui_LoginDialog.h"
#include "ClientEvents.h"
#include "../Common/CommLogin.h"
#include "ClientApplication.h"

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QWidget {
    Q_OBJECT
public:
    LoginDialog(ClientApplication *parent);

    ~LoginDialog();

private:
    //! The graphical ui used
    Ui::Form l_ui;
    //! Overload of the event method
    /*!
     *  \param event the event received
     *  \return the accept status of the event
     */
    void closeEvent(QCloseEvent *event);
    //! A pointer to its parent ClientApplication
    ClientApplication *parent;

private slots:
    //! callback of the connect button, it send an event to NetworkManager
    void on_connectButton_clicked();
};

#endif // LOGINDIALOG_H
