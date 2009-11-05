#include "MailDataPlugin.h"
#include "MailData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

MailData* MailDataPlugin::getMail(quint32 i)
{
   foreach (MailData* wb, Mails)
    {
		if (wb->_id == i)
		{
			return wb;
		}
	}
	MailData* wb = new MailData(this);
	Mails.append(wb);
	return wb;
}


MailData* MailDataPlugin::createMail()
{
	MailData* u = new MailData(this);
	Mails.append(u);
    return u;
}


Data* MailDataPlugin::getDataWithKey(QDataStream& s)
{
	quint32 Id;
	s >> Id;
	return getMail(Id);
}

#ifdef HORUS_CLIENT
void MailDataPlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
}
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/pop_3.h"
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"

QList<Data*> MailDataPlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
/*
foreach (UserData* data, users)
if (data->lastChange() >= date && data->status() == Data::UPTODATE)
	list.append(data);
        if (_totalmsg > 0)
    {
        qDebug() << _totalmsg << " to retrieve";
        getAllMail(_totalmsg);
    }

    this->exit(0);
*/

QList<Mail*> panier;
Pop_3 *servpop3 = new Pop_3("testzoidberg", "optrex42", "pop.free.fr");
servpop3->run();
qDebug() << servpop3->getTotalmsg();
if (servpop3->getTotalmsg() > 0)
{
            panier = servpop3->getAllMail(servpop3->getTotalmsg());
}
qDebug() << "panier.count";
if (panier.count() > 0)
{
    foreach (Mail* mail, panier)
    {
        MailData* dmail = createMail();
        qDebug() << "getShowText";
        dmail->setContent(mail->getShowText());
        qDebug() << "append";
        list.append(dmail);
    }
}
qDebug() << "return";
//connect(servpop3, SIGNAL(newMail(Mail*)), this, SLOT(SendMailToClient(Mail*)));
    //servpop3->getAllMails();

	return list;
}



void MailDataPlugin::SendMailToClient(Mail*)
{
    qDebug() << "new Mail !!!";
}
#endif
