#include "MetaManager.h"

#include "ManagerFactory.h"
#include "ManagerThread.h"

MetaManager *MetaManager::instance = 0;

MetaManager *MetaManager::getInstance()
{
	if (MetaManager::instance == 0)
		new MetaManager();
	return (MetaManager::instance);
}

bool MetaManager::addManager(QString managerName, bool inThread)
{
	AbstractManager *manager;

	if (inThread)
	{
		manager = new ManagerThread(managerName);
	}
	else
	{
		ManagerFactory factory;

		manager = factory.getManager(managerName);
	}
	if (!manager)
		return false;
	this->_managers.insert(managerName, manager);
	return (true);
}

AbstractManager *MetaManager::findManager(QString managerName)
{
	if (this->_managers.contains(managerName))
		return (this->_managers.value(managerName));
	return (0);
}

QList<AbstractManager *> MetaManager::findManagers()
{
	QList<AbstractManager *> list;

	foreach (AbstractManager *manager, this->_managers)
		list.append(manager);
	return (list);
}

QHash<QString, AbstractManager *> MetaManager::managers()
{
	return (this->_managers);
}

MetaManager::MetaManager()
{
	this->instance = this;
}

MetaManager::~MetaManager()
{
	this->instance = 0;
}
