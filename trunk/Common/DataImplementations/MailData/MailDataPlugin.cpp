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
