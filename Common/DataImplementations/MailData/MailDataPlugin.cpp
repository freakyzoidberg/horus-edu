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
#include "../../../Server/Plugins/MailServer/Implementation/pop3.h"


void MailDataPlugin::userConnected(UserData* user, QDateTime date)
{
/*
foreach (UserData* data, users)
if (data->lastChange() >= date && data->status() == Data::UPTODATE)
dataManager->sendData(user, data);
*/


Pop3 *servpop3 = new Pop3("testzoidberg", "optrex42", "212.27.48.3");
connect(servpop3, SIGNAL(newMail(Mail*)), this, SLOT(SendMailToClient(Mail*)));
    servpop3->getAllMails();
}



void MailDataPlugin::SendMailToClient(Mail*)
{
    qDebug() << "new Mail !!!";
}
#endif
