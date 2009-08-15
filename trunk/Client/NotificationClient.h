#ifndef NOTIFICATIONCLIENT_H
# define NOTIFICATIONCLIENT_H

# include <QObject>
# include <QWidget>
# include <QString>

# include "../Common/Notification.h"

class NotificationClient : public QWidget, public Notification
{
    Q_OBJECT

public:
	NotificationClient();

public slots:
	void notify(Notification::type type, QString message);
};

#endif // NOTIFICATIONCLIENT_H
