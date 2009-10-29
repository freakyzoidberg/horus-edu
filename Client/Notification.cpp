#include "Notification.h"

#include <QMessageBox>
#include <QCoreApplication>
#include "Debugger.h"

Notification *Notification::instance()
{
	static Notification* _instance = 0;
	if ( ! _instance)
	{
		_instance = new Notification;
		_instance->moveToThread(QCoreApplication::instance()->thread());
	}

	return _instance;
}

void Notification::notify(QtMsgType type, const char *message)
{
	notify((NotificationType)type, message);
}

void Notification::notify(NotificationType type, const char *message)
{
	static const char* directions[] =
	{
		"debug",
		"warning",
		"critical",
		"fatal",
		"message",
		"yesNo",
		"retry"
	};

	QMetaObject::invokeMethod(instance(), directions[type], Q_ARG(const QString, message));
}

void	Notification::debug(const QString message)
{
	Debugger::instance()->addDebugMessage(message);
}

void	Notification::message(const QString message)
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

void	Notification::warning(const QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle(tr("Horus"));
	msgBox.setText(tr("A non critical error occured:"));
	msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.exec();
}

void	Notification::critical(const QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle(tr("Horus"));
	msgBox.setText(tr("A critical error occured:"));
	msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
}

void	Notification::fatal(const QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle(tr("Horus"));
	msgBox.setText(tr("A fatal error occured:"));
	msgBox.setInformativeText(message);
	msgBox.setDetailedText(tr("This critical error is fatal and unrecoverable. You can put your computer in the trash and buy a new one."));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
	delete qApp;
}

void	Notification::yesNo(const QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle(tr("Horus"));
	msgBox.setText(message);
	msgBox.setInformativeText(tr(""));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.exec();
}

void	Notification::retry(const QString message)
{
	QMessageBox msgBox;

	msgBox.setWindowTitle(tr("Horus"));
	msgBox.setText(message);
	msgBox.setInformativeText(tr(""));
	msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Retry);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.exec();
}
