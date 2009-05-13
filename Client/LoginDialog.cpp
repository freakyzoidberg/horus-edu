#include "LoginDialog.h"


LoginDialog::LoginDialog(QObject *parent) : QWidget::QWidget()
{
    l_ui.setupUi(this);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        l_ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void LoginDialog::on_connectButton_clicked()
{
    if (l_ui.loginE->text() != "" || l_ui.passE->text() != "")
        NetworkManager::getInstance(this->parent())->login(l_ui.loginE->text(), l_ui.passE->text(), 1);
}
