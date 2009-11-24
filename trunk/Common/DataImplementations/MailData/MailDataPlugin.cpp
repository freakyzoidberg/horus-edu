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
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/pop_3.h"
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"
void MailDataPlugin::userConnected(UserData* user)
{
	Pop_3 servpop3(user->login(),user->login(), "localhost");
	if (servpop3.run())
		if (servpop3.getTotalmsg() > 0)
			foreach (Mail* mail, servpop3.getAllMail(servpop3.getTotalmsg()))
			{
				MailData* dmail = new MailData(this);

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

void MailDataPlugin::SendMailToClient(Mail*)
{
    qDebug() << "new Mail !!!";
}
#endif
