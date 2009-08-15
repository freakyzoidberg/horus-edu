#include "NotificationClient.h"

#include <QMessageBox>
#include <QCoreApplication>

#include "LoginDialog.h"

NotificationClient *NotificationClient::instance = 0;

NotificationClient::NotificationClient() : QObject()
{
	this->debugDialog = new QErrorMessage();
	this->debugDialog->setWindowTitle("Horus");
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
		default:
			this->fatal(qne->message);
		}
		return (true);
	}
	return (QObject::event(event));
}

void    NotificationClient::notify(Notification::type type, QString message)
{
	switch (type)
	{
	case DEBUG:
		this->debug(message);
		break ;
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
	default:
		this->fatal(message);
	}	
}

void	NotificationClient::debug(QString message)
{
	this->debugDialog->showMessage(message);
}

void	NotificationClient::message(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText(message);
	msgBox.setInformativeText("");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.exec();
}

void	NotificationClient::warning(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText("A non critical error occured:");
	msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.exec();
}

void	NotificationClient::error(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText("A critical error occured:");
	msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
}

void	NotificationClient::fatal(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText("A fatal error occured:");
	msgBox.setInformativeText(message);
	msgBox.setDetailedText("This critical error is fatal and unrecoverable. You can put your computer in the trash and buy a new one.");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
	delete qApp;
}

void	NotificationClient::yesNo(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText(message);
	msgBox.setInformativeText("");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.exec();
}

void	NotificationClient::retry(QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle("Horus");
	msgBox.setText(message);
	msgBox.setInformativeText("");
	msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Retry);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.exec();
}

void	NotificationClient::login(QString message)
{
	LoginDialog *loginDialog;

	loginDialog = new LoginDialog();
	loginDialog->show();
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
