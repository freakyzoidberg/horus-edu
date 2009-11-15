#ifndef				__MANAGEPARENTS_H__
# define			__MANAGEPARENTS_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>

# include			"../../../../../Common/PluginManager.h"
# include			"DisplayParent.h"

class				ManageParents : public QWidget
{
	Q_OBJECT

public:
	ManageParents(QWidget *parent, PluginManager *pluginManager);

private:
	QListView		*listView;
        DisplayParent           *displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;

private slots:
	void			parentSelected(const QModelIndex &current, const QModelIndex &previous);
	void			parentAdded();
	void			parentEdited();
	void			parentDeleted();
};

#endif
