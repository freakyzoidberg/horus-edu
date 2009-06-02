#include "LoginDialog.h"
#include "ThreadNetwork.h"


LoginDialog::LoginDialog(ClientApplication *parent) : QWidget::QWidget()
{
    this->parent = parent;
    l_ui.setupUi(this);
}

LoginDialog::~LoginDialog()
{
}


void    LoginDialog::closeEvent(QCloseEvent *event)
{
    QApplication::postEvent(ThreadNetwork::getInstance(this->parent), new QEvent(ClientEvents::OfflineModeEvent));
}

bool    LoginDialog::event(QEvent *event)
{
    return (QWidget::event(event));
}

void    LoginDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() + 1 == Qt::Key_Enter)
        connectMethod();
}

void LoginDialog::on_connectButton_clicked()
{
    connectMethod();
}

void    LoginDialog::connectMethod()
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
        QApplication::postEvent(ThreadNetwork::getInstance(), new SendLoginEvent(l.getPacket()));
        settings.endGroup();
        qDebug() << "[ out]" << l;
    }
}
