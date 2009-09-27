#include "ManagerFactory.h"

#include <QObject>
#include <QDebug>

#include "NetworkManager.h"
#include "PluginManagerClient.h"

AbstractManager *ManagerFactory::getManager(QString managerName)
{
	if (managerName == "NetworkManager")
		return (this->buildNetworkManager());
	if (managerName == "PluginManager")
		return (this->buildPluginManager());
	qDebug() << QObject::tr("ManagerFactory::getManager: Manager ") << managerName << QObject::tr(" not found.");
	return (0);
}

AbstractManager *ManagerFactory::buildNetworkManager()
{
	return (new NetworkManager());
}

AbstractManager *ManagerFactory::buildPluginManager()
{
    return (new PluginManagerClient());
}
