#include "InterfaceClient.h"

InterfaceClient::InterfaceClient(PluginManager *pM)
{
    this->pM = pM;
}

IClientPlugin   *InterfaceClient::getPlugin(const QByteArray name) const
{
    return (pM->findPlugin(QString(name)));
}
