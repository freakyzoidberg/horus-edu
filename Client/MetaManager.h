#ifndef		__METAMANAGER_H__
# define	__METAMANAGER_H__

# include <QString>
# include <QHash>
# include <QList>

# include "../Common/AbstractManager.h"

class MetaManager
{
private:
// Properties
	static MetaManager *instance;

// Methods
public:
	static MetaManager *getInstance();
	bool addManager(QString managerName, bool inThread);
	AbstractManager *findManager(QString managerName);
	template <typename T> 
	inline T findManager()
	{
		T desiredManager;

		foreach (AbstractManager *manager, this->_managers)
			if ((desiredManager = qobject_cast<T>(manager)))
				return (desiredManager);
		return (0);
	}
	QList<AbstractManager *> findManagers();
	QHash<QString, AbstractManager *> managers();

private:
	MetaManager();
	~MetaManager();
	QHash<QString, AbstractManager *> _managers;
};

#endif