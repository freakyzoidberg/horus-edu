#include "NotificationClient.h"

#include <QMessageBox>

NotificationClient::NotificationClient() : QWidget()
{
}

void    NotificationClient::notify(Notification::type type, QString message)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.exec();
}
