#ifndef NOTIFICATIONCLIENT_H
# define NOTIFICATIONCLIENT_H

# include <QObject>
# include <QString>
# include <QtGlobal>

//QtMsgType can be cast to NotificationType
enum NotificationType {
	DEBUG,		//0 = QtDebugMsg
	WARNING,	//1 = QtWarningMsg
	CRITICAL,	//2 = QtCriticalMsg
	FATAL,		//3 = QtFatalMsg
	MESSAGE,
	YES_NO,
	RETRY
};

class Notification : public QObject
{
	Q_OBJECT

public:
	static void				notify(QtMsgType        type, const char *message);
	static void				notify(NotificationType type, const char *message);

private slots:
	void					debug   (const QString message);
	void					warning (const QString message);
	void					critical(const QString message);
	void					fatal   (const QString message);
	void					message (const QString message);
	void					yesNo   (const QString message);
	void					retry   (const QString message);

private:
	static Notification*	instance();
	Notification() {};
	~Notification() {};
};

#endif // NOTIFICATIONCLIENT_H
