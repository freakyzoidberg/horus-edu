#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(QEvent *event)
{
    this->event = event;
}

bool    PluginNetwork::eventHandler()
{
    return true;
}

void    PluginNetwork::retrievedPacket()
{
    return ;
}

void    PluginNetwork::buildPacket()
{
    return ;
}
