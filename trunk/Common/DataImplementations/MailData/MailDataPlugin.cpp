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
#include "MailDataPlugin.h"
#include "MailData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

MailData* MailDataPlugin::mail(QString i)
{
	foreach (Data* d, _allDatas)
	{
		MailData* m = (MailData*)d;
		if (m->_id == i)
			return m;
	}

	MailData* m = new MailData(this);
	_allDatas.append(m);
	return m;
}

MailData* MailDataPlugin::createMail()
{
	MailData* u = new MailData(this);
	_allDatas.append(u);
	qDebug() << "Mails total : " << _allDatas.count();
	return u;
}

Data* MailDataPlugin::dataWithKey(QDataStream& s)
{
	QString Id;
	s >> Id;
	return mail(Id);
}

#ifdef HORUS_CLIENT

void MailDataPlugin::dataHaveNewKey(Data*, QDataStream&)
{
}

#include "../../../Client/DataListModel.h"

QAbstractListModel* MailDataPlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}

#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/pop_3.h"
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"
void MailDataPlugin::userConnected(UserData* user)
{

    QString host = QSettings().value("MAIL/MAIL_HOSTNAME", ".").toString();
    if (QSettings().value("MAIL/MAIL_SERV", "0").toInt() > 0)
    {
    Pop_3 servpop3(user->login()+"@"+QSettings().value("MAIL/MAIL_DOMAIN", "0").toString(),QByteArray::fromBase64(QVariant(user->mailPassord()).toByteArray()), host);
	if (servpop3.run())
        {

		if (servpop3.getTotalmsg() > 0)
                {

			foreach (Mail* mail, servpop3.getAllMail(servpop3.getTotalmsg()))
			{
				MailData* dmail = new MailData(this);

                                dmail->setBox("INBOX");
				dmail->setContent(mail->getShowText());
				dmail->setFrom(mail->from());
				dmail->setSubject(mail->subject());
				dmail->setMDate(mail->timeStamp());
				dmail->setId(mail->Getuid());
				dmail->_status = Data::UPTODATE;
				dmail->sendToUser(user);

				delete dmail;
			}
                 }
                else
                {

                }
            }
    }
}

void MailDataPlugin::SendMailToClient(Mail*)
{
    qDebug() << "new Mail !!!";
}
#endif
