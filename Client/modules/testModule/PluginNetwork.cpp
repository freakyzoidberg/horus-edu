#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(QEvent *event)
{
    this->event = event;
}

bool    PluginNetwork::handler()
{
    return true;
}
