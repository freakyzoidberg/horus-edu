#ifndef				__MANAGEPARENTS_H__
# define			__MANAGEPARENTS_H__

# include			<QWidget>

# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
//# include			"ListParents.h"
# include			"EditParent.h"

class				ManageParents : public QWidget
{
	Q_OBJECT

public:
	ManageParents(QWidget *parent, PluginManager *pluginManager);

private:
	PluginManager	*_pluginManager;
	//ListParents		*list;
	EditParent		*edit;
	QBoxLayout		*layout;

private slots:
	void			parentEdited(UserData *user);
	void			editExited();
};

#endif
