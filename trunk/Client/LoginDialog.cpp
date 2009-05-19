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
        QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
        settings.beginGroup("SESSIONS");
        settings.setValue("sessionString", "");
        settings.setValue("sessionLogin", l_ui.loginE->text());
        settings.setValue("sessionTime", "");
        settings.setValue("sessionEnd", "");
        CommLogin  l(CommLogin::LOGIN_PASSWORD);
        l.login = l_ui.loginE->text();
        l.sha1Pass = QCryptographicHash::hash(l_ui.passE->text().toUtf8(), QCryptographicHash::Sha1);
        emit sendPacket(l.getPacket());
        settings.endGroup();
        qDebug() << "[ out]" << l;
    }
}
