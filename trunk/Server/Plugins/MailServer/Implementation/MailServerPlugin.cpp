#include "MailServerPlugin.h"
#include "smtp.h"
void MailServerPlugin::receivePacket(UserData* user, const PluginPacket)
{
    emit sendPacket(user, PluginPacket("TestNetworkPlugin", "test retour", "test retour"));
}

bool MailServerPlugin::sendmail(QString host, quint32 port, QString login, QString pass, QString sender, QString dest, QString subject, QString content)
{
    QStringList mylist;
    mylist.append(dest);
     smtp *test1 = new smtp(host, sender,mylist , subject, content);
                test1->setPriority(smtp::high);
                test1->send();
                delete test1;
    return true;
}
