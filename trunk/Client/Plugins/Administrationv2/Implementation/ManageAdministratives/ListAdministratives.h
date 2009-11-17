#ifndef				__LISTADMINISTRATIVES_H__
# define			__LISTADMINISTRATIVES_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayAdministrative.h"

class				ListAdministratives : public QWidget
{
	Q_OBJECT

public:
	ListAdministratives(QWidget *parent, PluginManager *pluginManager);

private:
	QListView		*listView;
	DisplayAdministrative	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			AdministrativeSelected(const QModelIndex &current, const QModelIndex &previous);
	void			AdministrativeAdded();
	void			AdministrativeEdited();
	void			AdministrativeDeleted();

signals:
	void			editAdministrative(UserData *user);
};

#endif
