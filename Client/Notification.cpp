/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
//	Debugger::instance()->addDebugMessage(message);
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
	qApp->exit(-1);
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
