#ifndef NOTIFICATIONCLIENT_H
# define NOTIFICATIONCLIENT_H

# include <QObject>
# include <QEvent>
# include <QString>
# include <QErrorMessage>

# include "../Common/Notification.h"

class NotificationClient : public QObject, public Notification
{
    Q_OBJECT

public:
	static NotificationClient *getInstance();
	bool event(QEvent *event);

public slots:
        void notify(Notification::type type, const QString message);

private:
	NotificationClient();
	~NotificationClient();
        void debug(const QString message);
        void message(const QString message);
        void warning(const QString message);
        void error(const QString message);
        void fatal(const QString message);
        void yesNo(const QString message);
        void retry(const QString message);
        void login(const QString message);
	
	static NotificationClient *instance;
	static void QtNotify(QtMsgType type, const char *message);

	friend void	QtNotify(QtMsgType type, const char *message);

	QErrorMessage *debugDialog;
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
