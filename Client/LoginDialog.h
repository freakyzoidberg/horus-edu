#ifndef LOGINDIALOG_H
# define LOGINDIALOG_H

# include <QWidget>
#include <QDialog>
# include <QObject>
# include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
# include "../Common/CommLogin.h"


//! This Object is the window to login in the server with a username and password
class LoginDialog : public QDialog
{
    Q_OBJECT

    public:
                                    LoginDialog();
    private:
            QLineEdit*	_login;
            QLineEdit*	_password;
    private slots:
            void		userSelected();
            void		otherUser();
            void		loginNewUser();
            void		keyPressEvent (QKeyEvent *event);
    //	//! callback of the connect button, it send an event to NetworkManager
    //    void on_connectButton_clicked();
    //protected slots:
    //    //! event loop
    //    bool    event(QEvent *e);
};

#endif // LOGINDIALOG_H
