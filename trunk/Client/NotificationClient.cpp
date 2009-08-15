#include "NotificationClient.h"

#include <QMessageBox>
#include <QCoreApplication>

NotificationClient *NotificationClient::instance = 0;

NotificationClient::NotificationClient() : QObject()
{
}

NotificationClient::~NotificationClient()
{
}

NotificationClient *NotificationClient::getInstance()
{
	if (!instance)
		instance = new NotificationClient();
	return (instance);
}

void	QtNotify(QtMsgType type, const char *message)
{
	QCoreApplication::postEvent(NotificationClient::getInstance(), new QtNotificationEvent(type, QString(message)));
}

bool	NotificationClient::event(QEvent *event)
{
	if (event->type() == QtNotificationEvent::type())
	{
		QtNotificationEvent *qne;

		qne = static_cast<QtNotificationEvent *>(event);
		switch (qne->msgType)
		{
		case QtDebugMsg:
			this->debug(qne->message);
			break ;
		case QtWarningMsg:
			this->warning(qne->message);
			break ;
		case QtCriticalMsg:
			this->error(qne->message);
			break ;
		case QtFatalMsg:
			this->fatal(qne->message);
			break ;
		}
		return (true);
	}
	return (QObject::event(event));
}

void    NotificationClient::notify(Notification::type type, QString message)
{
	switch (type)
	{
	case MESSAGE:
		this->message(message);
		break ;
	case WARNING:
		this->warning(message);
		break ;
	case ERROR:
		this->error(message);
		break ;
	case FATAL:
		this->fatal(message);
		break ;
	case YES_NO:
		this->yesNo(message);
		break ;
	case RETRY:
		this->retry(message);
		break ;
	case LOGIN:
		this->login(message);
		break ;
	}	
}

void	NotificationClient::debug(QString message)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.exec();
}
void	NotificationClient::message(QString message)
{
	this->debug(message);
}

void	NotificationClient::warning(QString message)
{
	this->debug(message);
}

void	NotificationClient::error(QString message)
{
	this->debug(message);
}

void	NotificationClient::fatal(QString message)
{
	this->debug(message);
}

void	NotificationClient::yesNo(QString message)
{
	this->debug(message);
}

void	NotificationClient::retry(QString message)
{
	this->debug(message);
}

void	NotificationClient::login(QString message)
{
	this->debug(message);
}

QEvent::Type QtNotificationEvent::Type = (QEvent::Type)QEvent::registerEventType();

QtNotificationEvent::QtNotificationEvent(QtMsgType _msgType, QString _message) : QEvent(QtNotificationEvent::Type)
{
	this->msgType = _msgType;
	this->message = _message;
}

QtNotificationEvent::QtNotificationEvent(QtNotificationEvent &copy) : QEvent(QtNotificationEvent::Type)
{
	this->msgType = copy.msgType;
	this->message = copy.message;
}

QEvent::Type QtNotificationEvent::type()
{
	return (QtNotificationEvent::Type);
}
