#ifndef				__MANAGEADMINISTRATIVES_H__
# define			__MANAGEADMINISTRATIVES_H__

# include			<QWidget>

# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"ListAdministratives.h"
# include			"EditAdministrative.h"

class				ManageAdministratives : public QWidget
{
	Q_OBJECT

public:
	ManageAdministratives(QWidget *parent, PluginManager *pluginManager);

private:
	PluginManager	*_pluginManager;
	ListAdministratives		*list;
	EditAdministrative		*edit;
	QBoxLayout		*layout;

private slots:
	void			AdministrativeEdited(UserData *user);
	void			editExited();
};

#endif
