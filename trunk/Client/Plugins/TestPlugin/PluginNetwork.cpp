#include "PluginNetwork.h"

PluginNetwork::PluginNetwork()
{
}

bool    PluginNetwork::eventHandler(QEvent *event)
{
    event = event; // remove 'unused parameter' warning !
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
