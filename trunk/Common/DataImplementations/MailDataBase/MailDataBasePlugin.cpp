#include "MailDataBasePlugin.h"
#include "MailDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "MailSender.h"

MailDataBasePlugin::MailDataBasePlugin()
{
    QString host = "smtp.free.fr";
    QString sender = "dev@horus-edu.net";
    QString dest = "dev@horus-edu.net";
    QString subject = "test";
    QString content = "Hay World from Horus Server";
    QStringList mylist;
    mylist.append(dest);
     MailSender *test1 = new MailSender(host, sender,mylist , "ahum", content);
                test1->setPriority(MailSender::high);
                test1->send();
                delete test1;


}

/*
MailData* MailDataBasePlugin::getSettings(QString part, quint8 scope, quint32 ownerId)
{
    foreach (MailData* setting, settings)
        if (setting->part() == part && setting->scope() == scope && setting->owner() == ownerId)
            return setting;

    MailDataBase* set = new MailDataBase(this, part, scope, ownerId);
    settings.append(set);
    return set;
}
*/

Data* MailDataBasePlugin::getDataWithKey(QDataStream& s)
{

}

#ifdef HORUS_SERVER
bool MailDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif

