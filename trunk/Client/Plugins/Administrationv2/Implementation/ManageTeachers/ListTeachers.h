#ifndef				__LISTTEACHERS_H__
# define			__LISTTEACHERS_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>
# include			<QSortFilterProxyModel>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayTeacher.h"

class				ListTeachers : public QWidget
{
	Q_OBJECT

public:
	ListTeachers(QWidget *parent, PluginManager *pluginManager);
	QListView		*listView;

private:
	DisplayTeacher	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QSortFilterProxyModel	*filter;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			TeacherSelected(const QModelIndex &current, const QModelIndex &previous);
	void			TeacherAdded();
	void			TeacherEdited();
	void			TeacherDeleted();
	void			TeacherUpdated(Data *data);

signals:
	void			editTeacher(UserData *user);
};

#endif
