#ifndef				__MANAGEPARENTS_H__
# define			__MANAGEPARENTS_H__

# include			<QWidget>

# include			"../../../../../Common/PluginManager.h"

class				ManageParents : public QWidget
{
public:
	ManageParents(QWidget *parent, PluginManager *pluginManager);

private:
	PluginManager	*_pluginManager;
};

#endif