#ifndef				__LISTPARENTS_H__
# define			__LISTPARENTS_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayParent.h"

class				ListParents : public QWidget
{
	Q_OBJECT

public:
	ListParents(QWidget *parent, PluginManager *pluginManager);
	QListView		*listView;

private:
	DisplayParent	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			parentSelected(const QModelIndex &current, const QModelIndex &previous);
	void			parentAdded();
	void			parentEdited();
	void			parentDeleted();
	void			ParentUpdated(Data *data);

signals:
	void			editParent(UserData *user);
};

#endif
