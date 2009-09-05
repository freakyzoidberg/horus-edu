#include "ManagerFactory.h"

#include <QDebug>

#include "NetworkManager.h"
#include "PluginManagerClient.h"

AbstractManager *ManagerFactory::getManager(QString managerName)
{
	if (managerName == "NetworkManager")
		return (this->buildNetworkManager());
	if (managerName == "PluginManager")
		return (this->buildPluginManager());
	qDebug() << "ManagerFactory::getManager: Manager " << managerName << " not found.";
	return (0);
}

AbstractManager *ManagerFactory::buildNetworkManager()
{
	return (new NetworkManager());
}

AbstractManager *ManagerFactory::buildPluginManager()
{
        return (PluginManagerClient::instance());
}
