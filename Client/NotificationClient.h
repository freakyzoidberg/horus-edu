#ifndef NOTIFICATIONCLIENT_H
# define NOTIFICATIONCLIENT_H

# include <QObject>
# include <QEvent>
# include <QString>

# include "../Common/Notification.h"

class NotificationClient : public QObject, public Notification
{
    Q_OBJECT

public:
	static NotificationClient *getInstance();
	bool event(QEvent *event);

public slots:
	void notify(Notification::type type, QString message);

private:
	NotificationClient();
	~NotificationClient();
	void debug(QString message);
	void message(QString message);
	void warning(QString message);
	void error(QString message);
	void fatal(QString message);
	void yesNo(QString message);
	void retry(QString message);
	void login(QString message);
	
	static NotificationClient *instance;
	static void QtNotify(QtMsgType type, const char *message);

	friend void	QtNotify(QtMsgType type, const char *message);

};

class QtNotificationEvent : public QEvent
{
public:
	QtNotificationEvent(QtMsgType _msgType, QString _message);
	QtNotificationEvent(QtNotificationEvent &copy);
	static QEvent::Type type();

	static QEvent::Type Type;
	QtMsgType msgType;
	QString message;
};

#endif // NOTIFICATIONCLIENT_H
