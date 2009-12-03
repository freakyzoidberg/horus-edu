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
#include "MailData.h"
#include "MailDataPlugin.h"
#include "../../PluginManager.h"


void MailData::keyToStream(QDataStream& s) const
{
	s << _id;
}

void MailData::dataToStream(QDataStream& s) const
{
    s << _id
    << _to
    << _cc
    << _bcc
    << _subject
    << _content
    << _from
    << _date
    << _box;
	Data::dataToStream(s);
}

void MailData::dataFromStream(QDataStream& s)
{
	s >>
	_id >>
	_to >>
	_cc >>
	_bcc >>
	_subject >>
        _content >>
        _from >>
        _date >>
        _box;
	Data::dataFromStream(s);
}

QDebug MailData::operator<<(QDebug debug) const
{
	return debug << tr("MailData::") << _id;
}

#ifdef HORUS_CLIENT

#include <QIcon>

QVariant	MailData::data(int column, int role) const
{
	if (role == Data::FILTER_ROLE)
		return (_box);
	if (role == Qt::DisplayRole)
	{
		if (column == 0)
			return (_subject + " From" + _from);
		if (column == 1)
			return (tr("Mail"));
    }
	return QVariant();
}

#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/smtp.h"
#include "../../../Server/Plugins/MailServer/Implementation/pop3.h"
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"
quint8 MailData::serverSave()
{
    QString host = QSettings().value("MAIL/MAIL_HOSTNAME", ".").toString();
    QString domain = QSettings().value("MAIL/MAIL_DOMAIN", ".").toString();



     smtp *test1 = new smtp(host, _plugin->pluginManager->currentUser()->login()+"@"+QSettings().value("MAIL/MAIL_DOMAIN", "0").toString(),this->_to , this->_subject, this->_content);

     if (_cc.count() > 0)
         test1->setCc(_cc);
     if (_bcc.count() > 0)
         test1->setBcc(_bcc);
                test1->setPriority(smtp::high);
                //test1->setSmtpServer("localhost");
                if (QSettings().value("MAIL/MAIL_SERV", "0") == 2)
                test1->setLogin(_plugin->pluginManager->currentUser()->login()+"@"+QSettings().value("MAIL/MAIL_DOMAIN", "0").toString(), QByteArray::fromBase64(QVariant(_plugin->pluginManager->currentUser()->mailPassord()).toByteArray()));
                test1->setPort(25);
                //test1->setSsl(true);

                test1->send();

                delete test1;
	return NONE;
}
/*
quint8 MailData::serverRead()
{

    //Pop3 *servpop3 = new Pop3(_plugin->pluginManager->currentUser()->login(), "toto", "localhost");
    Pop3 *servpop3 = new Pop3("testzoidberg", "optrex42", "pop.free.fr");
    QList<Mail *> panier;
    panier = servpop3->getAllMails();
    qDebug() << panier.count();

}
*/



#endif
