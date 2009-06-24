#include "InterfaceClient.h"
#include <QDebug>

InterfaceClient::InterfaceClient(PluginManager *pM)
{
    this->pM = pM;
}

IClientPlugin   *InterfaceClient::getPlugin(const QByteArray name) const
{
    qDebug() << "InterfaceClient:: get " << name << " -> " << pM->findPlugin(QString(name));
    return (pM->findPlugin(QString(name)));
}
