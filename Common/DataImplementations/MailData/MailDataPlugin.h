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
#ifndef MAILDATAPLUGIN_H
#define MAILDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"
#endif

class Data;
class TreeData;
class MailData;
class MailDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
	inline const QString pluginName()    const { return "MailDataPlugin"; }
	inline const QString pluginVersion() const { return "0.1"; }
	inline const QString dataType()   const { return "MailData"; }


		MailData* mail(QString i);
		MailData* createMail();
#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
public slots:
	void SendMailToClient(Mail*);
public:
	void userConnected(UserData* user);
#endif
private:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*                dataWithKey(QDataStream& s);
};

#endif // MAILDATAPLUGIN_H
