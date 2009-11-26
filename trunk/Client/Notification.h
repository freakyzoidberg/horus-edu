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
