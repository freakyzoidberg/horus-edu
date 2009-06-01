#include "InterfaceClient.h"

InterfaceClient::InterfaceClient(IClientPlugin *p, ClientApplication *parent)
{
    this->parent = parent;
    plugin = p;
}

IClientPlugin   *InterfaceClient::getPlugin(const QByteArray name) const
{
    return 0;
}
