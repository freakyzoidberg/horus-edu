#include "ManagerFactory.h"

#include <QDebug>

#include "NetworkManager.h"
#include "ConfigManager.h"
#include "PluginManagerClient.h"

AbstractManager *ManagerFactory::getManager(QString managerName)
{
	if (managerName == "NetworkManager")
		return (this->buildNetworkManager());
	if (managerName == "ConfigManager")
		return (this->buildConfigManager());
	if (managerName == "PluginManager")
		return (this->buildPluginManager());
	qDebug() << "ManagerFactory::getManager: Manager " << managerName << " not found.";
	return (0);
}

AbstractManager *ManagerFactory::buildNetworkManager()
{
	return (new NetworkManager());
}

AbstractManager *ManagerFactory::buildConfigManager()
{
	return (new ConfigManager());
}

AbstractManager *ManagerFactory::buildPluginManager()
{
	return (new PluginManagerClient());
}
