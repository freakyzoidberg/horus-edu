#include "NotificationClient.h"

#include <QMessageBox>

NotificationClient::NotificationClient() : QWidget()
{
}

void    NotificationClient::notify(QString message)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.exec();
}
