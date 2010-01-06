#include "MailsNetwork.h"

MailsNetwork::MailsNetwork()
{
}
void MailsNetwork::update()
{
    emit sendPacket(PluginPacket("Mail Network", "update"));
}
