#include "LoginDialog.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDir>
#include <QCryptographicHash>

#include "MetaManager.h"
#include "ClientEvents.h"


LoginDialog::LoginDialog() : QWidget()
{
    l_ui.setupUi(this);
    l_ui.passE->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
}

void    LoginDialog::closeEvent()
{
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new QEvent(ClientEvents::OfflineModeEvent));
}

bool    LoginDialog::event(QEvent *event)
{
    return (QWidget::event(event));
}

void    LoginDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
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
        QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
        settings.beginGroup("SESSIONS");
        settings.setValue("sessionString", "");
        settings.setValue("sessionLogin", l_ui.loginE->text());
        settings.setValue("sessionTime", "");
        settings.setValue("sessionEnd", "");
        CommLogin  l(CommLogin::LOGIN_PASSWORD);
        l.login = l_ui.loginE->text();
        l.password = QCryptographicHash::hash(l_ui.passE->text().toUtf8(), QCryptographicHash::Sha1);
        QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(l.getPacket()));
        settings.endGroup();
		delete this;
    }
}
