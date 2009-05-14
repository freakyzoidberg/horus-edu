#include "LoginDialog.h"


LoginDialog::LoginDialog(QObject *parent) : QWidget::QWidget()
{
    this->parent = parent;
    l_ui.setupUi(this);
}

LoginDialog::~LoginDialog()
{
}


/*bool    LoginDialog::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoginEvent)
    {
    }
    return true;
}*/

void LoginDialog::on_connectButton_clicked()
{
    if (l_ui.loginE->text() != "" || l_ui.passE->text() != "")
    {
        LoginEvent *e = new LoginEvent(l_ui.loginE->text(),l_ui.passE->text(), 1);
        QApplication::postEvent(this->parent, e);
    }
}
