#include "MailNetwork.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
MailNetwork::MailNetwork()
{
}

void MailNetwork::receivePacket(UserData* user, const PluginPacket packet)
{
this->pluginManager->findPlugin<MailDataPlugin*>()->userConnected(user);

}
