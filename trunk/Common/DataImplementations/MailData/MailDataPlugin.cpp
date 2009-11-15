#include "MailDataPlugin.h"
#include "MailData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

MailData* MailDataPlugin::getMail(QString i)
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

QList<MailData*> MailDataPlugin::getAllMail() const
{
        QList<MailData*> list;
        foreach (MailData* data, Mails)
            if (data->getId() != "")
                        list.append(data);

       // list.pop_back();
        return list;
}

MailData* MailDataPlugin::createMail()
{
	MailData* u = new MailData(this);
	Mails.append(u);
        qDebug() << "Mails total : " << Mails.count();
    return u;
}


Data* MailDataPlugin::dataWithKey(QDataStream& s)
{
        QString Id;
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
Pop_3 *servpop3 = new Pop_3(user->login(),user->login(), "localhost");
if (servpop3->run())
if (servpop3->getTotalmsg() > 0)
{
            panier = servpop3->getAllMail(servpop3->getTotalmsg());
}

if (panier.count() > 0)
{
    foreach (Mail* mail, panier)
    {
        MailData* dmail = createMail();

        dmail->setContent(mail->getShowText());

qDebug() << mail->from();
        dmail->setFrom(mail->from());
        qDebug() << mail->from();
        dmail->setSubject(mail->subject());
        qDebug() << mail->timeStamp();
        dmail->setMDate(mail->timeStamp());
        dmail->setId(mail->Getuid());

        list.append(dmail);
    }
}

//connect(servpop3, SIGNAL(newMail(Mail*)), this, SLOT(SendMailToClient(Mail*)));
    //servpop3->getAllMails();

	return list;
}



void MailDataPlugin::SendMailToClient(Mail*)
{
    qDebug() << "new Mail !!!";
}
#endif
