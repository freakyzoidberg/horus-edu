#ifndef				__LISTADMINISTRATIVES_H__
# define			__LISTADMINISTRATIVES_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>
# include			<QSortFilterProxyModel>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayAdministrative.h"

class				ListAdministratives : public QWidget
{
	Q_OBJECT

public:
	ListAdministratives(QWidget *parent, PluginManager *pluginManager);
	QListView		*listView;

private:
	DisplayAdministrative	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QSortFilterProxyModel	*filter;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			AdministrativeSelected(const QModelIndex &current, const QModelIndex &previous);
	void			AdministrativeAdded();
	void			AdministrativeEdited();
	void			AdministrativeDeleted();
	void			AdministrativeUpdated(Data *data);

signals:
	void			editAdministrative(UserData *user);
};

#endif
