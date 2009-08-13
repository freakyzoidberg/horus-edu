#ifndef __MANAGER_H__
# define __MANAGER_H__

# include "AbstractManager.h"

class Manager : public AbstractManager
{
	Q_OBJECT
public:
	virtual ~Manager();
};

#endif
