#ifndef __MANAGERFACTORY_H__
# define __MANAGERFACTORY_H__

# include <QString>

# include "AbstractManager.h"

class ManagerFactory
{
	// Methods
public:
	AbstractManager *getManager(QString managerName);

private:
	AbstractManager *buildNetworkManager();
	AbstractManager *buildConfigManager();
	AbstractManager *buildPluginManager();
};

#endif // MANAGERFACTORY_H
