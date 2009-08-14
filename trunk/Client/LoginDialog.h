#ifndef LOGINDIALOG_H
# define LOGINDIALOG_H

# include <QWidget>
# include <QObject>
# include <QKeyEvent>

# include "../Common/CommLogin.h"

# include "ui_LoginDialog.h"

//! This Object is the window to login in the server with a username and password
class LoginDialog : public QWidget
{
    Q_OBJECT

public:
    LoginDialog();
    ~LoginDialog();

private:
    //! The graphical ui used
    Ui::Form l_ui;
    //! Overload of the CloseEvent method
    void closeEvent();
    //! Method to send an event to networkManager
    void        connectMethod();
private slots:
    //! callback of the connect button, it send an event to NetworkManager
    void on_connectButton_clicked();
protected slots:
    //! event loop
    bool    event(QEvent *e);
    void    keyPressEvent (QKeyEvent *event);
};

#endif // LOGINDIALOG_H
